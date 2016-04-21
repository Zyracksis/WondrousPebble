#include <pebble.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
   
#define MAX_SEQUENCE 1000
#define MAX_INPUT 30
#define MAX_TERM 6
   
static Window *window;
static TextLayer *text_layer;


// What happens when we click select
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  int *input = context;
  text_layer_set_text(text_layer, "Starting algorithm...");
  static char sequence[MAX_SEQUENCE];
  static char buffer[MAX_TERM];
  int a;
  strcpy(sequence, "Sequence: \n ");
  if (*input < 1) {
       text_layer_set_text(text_layer, "Bad input");
  } else {
    while (*input > 1) {
      a = snprintf(buffer, MAX_TERM, "%d, ",  *input);
      a++;
      strcat(sequence, buffer);
      if (*input % 2 == 0) {
         *input = *input / 2;
      } else {
         *input = 3 * *input + 1;
      }
      printf("Value: %d, String: %s \n", *input, sequence);
    }
    strcat(sequence, "1.");
    text_layer_set_text(text_layer, sequence);   
  }                 
}

                           
// What happens when the up button is pressed
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  int *input = context;
  *input = *input + 1;
  static char string[MAX_INPUT];
  int a = snprintf(string, MAX_INPUT, "Input: %d",  *input);
  if (a > MAX_INPUT) {}
   
  text_layer_set_text(text_layer, string);
}

// What happens when the down button is pressed
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  int *input = context;
  *input = *input - 1;
  //int test = 50;
  static char string[MAX_INPUT];
  //char *buffer = string;
  int a = snprintf(string, MAX_INPUT, "Input: %d",  *input);
  if (a > MAX_INPUT) {}
   
  text_layer_set_text(text_layer, string);
}

// Set the subscriptions for each button press
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

// Create the initial window
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  //GRect bounds = layer_get_bounds(window_layer);
  text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { /*bounds.size.w*/ 144, 168} });
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  text_layer_set_background_color(text_layer, GColorBlack);
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_text(text_layer, "Please input your number!");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

// Destroy the initial window
static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}




// What to do on startup
static void init(void) {
  int input = 0;
  int *inputPointer = &input;
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  window_set_click_config_provider_with_context(window, click_config_provider, inputPointer);
  const bool animated = true;
  window_stack_push(window, animated);
   
}

static void deinit(void) {
  //window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
#include "readline.h"
#include "history.h"

char* athame_buffer_store = 0;
static char* ap_get_line_buffer()
{
  if (rl_end == 0)
  {
    return "";
  }
  if(athame_buffer_store)
  {
    free(athame_buffer_store);
  }
  return athame_buffer_store = strndup(rl_line_buffer, rl_end);
}

static int ap_get_line_buffer_length()
{
  return rl_end;
}

static void ap_set_line_buffer(char* newText)
{
  rl_replace_line(newText, 0);
}

static int ap_get_cursor()
{
  return rl_point;
}

static void ap_set_cursor(int c)
{
  rl_point = c;
}

static void ap_display()
{
  rl_redisplay();
}

static void ap_force_display()
{
  rl_forced_update_display();
}

static int ap_get_term_width()
{
  int height, width;
  rl_get_screen_size(&height, &width);
  return width;
}

static int ap_get_term_height()
{
  int height, width;
  rl_get_screen_size(&height, &width);
  return height;
}

static int ap_get_prompt_length()
{
  return rl_expand_prompt(rl_prompt);
}

HISTORY_STATE* hs;
int hs_counter;
static void ap_get_history_start()
{
  hs = history_get_history_state(); 
  hs_counter = 0;
}

static char* ap_get_history_next()
{
  if (hs->entries[hs_counter])
  {
    return hs->entries[hs_counter++]->line;
  }
  else
  {
    return NULL;
  }
}

static void ap_get_history_end()
{
  xfree(hs);
}

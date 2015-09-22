#include "comm.h"
  
static unsigned int HexStringToUInt(char const* str) {
  unsigned int value = 0;
  
  if ( str == NULL ) return 0;
  
  char const* ptr = str;
  if ( *ptr == '#' ) ++ptr; 
  else if ( *ptr == '0' && *(ptr+1) =='x' ) ptr += 2;
  
  for ( ; *ptr != '\0'; ++ptr ) {
    unsigned c = *ptr;
    value <<= 4;    
    if( c >= '0' && c <= '9' ) {
      value += ( c - '0' );
    }
    else if( c >= 'A' && c <= 'F' ) {
      value += ( c - 'A' + 10 );
    }
    else if( c >= 'a' && c <= 'f' ) {
      value += ( c - 'a' + 10 );
    }
    else {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "ERROR: Non hexadecimal string \"%s\"", str);
      return 0;
    }
  }
  return value;  
}

static void in_recv_handler(DictionaryIterator *iter, void *context) {
  Tuple *t = dict_read_first(iter);
  while(t) {
    bool isTrue = strcmp(t->value->cstring, "true") == 0;
    bool isFalse = strcmp(t->value->cstring, "false") == 0;
    
    if (isTrue || isFalse) {
      persist_write_bool(t->key, isTrue);    
    }
    else {
      int value = HexStringToUInt(t->value->cstring);
      persist_write_int(t->key, value);
//      APP_LOG(APP_LOG_LEVEL_DEBUG, "Wrote %d=\"%d\"", (int)t->key, value);
    }
    t = dict_read_next(iter);
  }

  // Refresh live store
  config_init();
  vibes_short_pulse();
}

void comm_init() {
  app_message_register_inbox_received(in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}
var VERSION = "0.2";

Pebble.addEventListener('ready', function(e) {
  console.log('PebbleKit JS ready! Version: ' + VERSION);
});

Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL('https://hw.github.io/thin-markers/index.html?version=' + VERSION);
});

Pebble.addEventListener('webviewclosed', function(e) {
  console.log('Webview closed');

  var json = JSON.parse(decodeURIComponent(e.response));

  var options = {
    "PERSIST_KEY_DATE": '' + json.date,
    "PERSIST_KEY_DAY": '' + json.day,
    "PERSIST_KEY_BT": '' + json.bluetooth,
    "PERSIST_KEY_BATTERY": '' + json.battery,
    "PERSIST_KEY_SECOND_HAND": '' + json.second_hand,
    "PERSIST_KEY_HOUR_MARKERS_COLOR": '' + json.hour_markers_color,
    "PERSIST_KEY_MINUTE_MARKERS_COLOR": '' + json.minute_markers_color,
    "PERSIST_KEY_CHARGING_MARKERS_COLOR": '' + json.charging_markers_color,
    "PERSIST_KEY_HANDS_COLOR": '' + json.hands_color,
    "PERSIST_KEY_TIPS_COLOR": '' + json.tips_color,
    "PERSIST_KEY_SECOND_HAND_COLOR": '' + json.second_hand_color,
    "PERSIST_KEY_SECOND_TIP_COLOR": '' + json.second_tip_color,
    "PERSIST_KEY_CALENDAR_DAY_COLOR": '' + json.calendar_day_color,
  };
  Pebble.sendAppMessage(options,
    function(e) {
      console.log('Settings update successful!');
    },
    function(e) {
      console.log('Settings update failed: ' + JSON.stringify(e));
    });
}); 
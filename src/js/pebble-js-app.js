Pebble.addEventListener('ready', function() {
    //console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
    var url = 'https://rawgit.com/soomtong/HannaClock/master/config/index.html';
    //console.log('Showing configuration page: ' + url);

    Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
    var configData = JSON.parse(decodeURIComponent(e.response));
    //console.log('Configuration page returned: ' + JSON.stringify(configData));

    var dict = {};

    if(configData['feedback_pomodoro'] === true) {
        dict['KEY_FEEDBACK_POMODORO'] = configData['feedback_pomodoro'] ? 1 : 0;  // Send a boolean as an integer
        dict['KEY_FEEDBACK_POMODORO_CYCLE'] = configData['feedback_pomodoro_cycle'] ? Number(configData['feedback_pomodoro_cycle']) : 0;
    } else {
        dict['KEY_FEEDBACK_POMODORO'] = 0;
        dict['KEY_FEEDBACK_POMODORO_CYCLE'] = 0;
    }

    // Send to watchapp
    Pebble.sendAppMessage(dict, function() {
        console.log('Send successful: ' + JSON.stringify(dict));
    }, function() {
        console.log('Send failed!');
    });
});
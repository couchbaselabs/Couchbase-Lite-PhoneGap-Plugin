# PhoneGap plugin for Couchbase Lite

Couchbase Lite is an embedded JSON database for occasionally connected devices. It syncs data in the background, so users can collaborate across devices. There is an event based `_changes` JSON feed API so you can drive data-binding UI frameworks like Sencha and Backbone to reflect remote updates interactively.

It works with native code as well as Cordova / PhoneGap on iOS and Android (you can even sync with Mac desktops), so it doesn't matter where your users are, they can work with the data, and as soon as they get back online, everyone will see their changes.

[Learn more about Couchbase Lite](http://developer.couchbase.com/mobile/).

## Quick start

You install Couchbase Lite into your PhoneGap app using [the PhoneGap command line tools](https://github.com/phonegap/phonegap-cli/) and this command (where `$PLATFORM` is either `ios` or `android`):

```
npm install -g phonegap
phonegap create MyPhoneGapApp
cd MyPhoneGapApp/
phonegap local plugin add https://github.com/couchbaselabs/Couchbase-Lite-PhoneGap-Plugin.git
phonegap run $PLATFORM
```

Congrats, you got to hello world. If you want to try a full example app, [follow the instructions for 5 minutes to awesome](http://docs.couchbase.com/couchbase-lite/cbl-phonegap/#getting-started-in-5-minutes)

## Architecture

This is where the plugin fits in the picture:

![architecture.png](http://cl.ly/image/3b15030Y3f0q/couchbase-lite-phonegap-plugin-android.png)

_Note:_ your JavaScript code can also directly communicate with Couchbase Lite over a Javascript<->Native bridge, to [ask it what URL it has launched on for subsequent XHR access](https://github.com/couchbaselabs/LiteGap/blob/master/www/litegap-example.html)

# Where to go from here

There's an [example chat app with PhoneGap](https://github.com/couchbaselabs/CouchChat-PhoneGap) that illustrates the channel sync API. You can [read more about the app here](https://github.com/couchbaselabs/CouchChat-PhoneGap).

If you made it this far, you are now ready to build your custom PhoneGap App by editing the HTML, CSS, and Javascript files under the www directory.  Your same application code will work on both the iOS and Android platforms!

[![githalytics.com alpha](https://cruel-carlota.pagodabox.com/6c4d5c48d78a787fd11642029c32bb88 "githalytics.com")](http://githalytics.com/couchbaselabs/Couchbase-Lite-PhoneGap-Plugin)

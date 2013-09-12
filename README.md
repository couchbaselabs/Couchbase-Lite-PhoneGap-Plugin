# PhoneGap plugin for Couchbase Lite

Couchbase Lite is an embedded JSON database for occasionally connected devices. It syncs data in the background, so users can collaborate across devices. There is an [event based `_changes` JSON feed API](http://guide.couchdb.org/draft/notifications.html) so you can drive data-binding UI frameworks like Sencha and Backbone to reflect remote updates interactively.

It works with native code as well as Cordova / PhoneGap on iOS and Android (you can even sync with Mac desktops), so it doesn't matter where your users are, they can work with the data, and as soon as they get back online, everyone will see their changes.

If you wanna know everything about the PhoneGap plugin system the [best docs right now are on Raymond Camden's blog](http://www.raymondcamden.com/index.cfm/2013/7/19/PhoneGap-30-Released--Things-You-Should-Know)

## Quick start

You install LiteGap into your PhoneGap app using [the PhoneGap command line tools](https://github.com/mwbrooks/phonegap-cli/) and this command (where `$PLATFORM` is either `ios` or `android`):

```
npm install -g phonegap
phonegap create MyPhoneGapApp 
cd MyPhoneGapApp/
phonegap local plugin add https://github.com/couchbaselabs/Couchbase-Lite-PhoneGap-Plugin.git
phonegap run $PLATFORM
```

Congrats, you got to hello world. If you want to get awesome, do this:

```
rm -rf www
git clone https://github.com/couchbaselabs/TodoLite-PhoneGap www
phonegap run $PLATFORM
```

You should see a cool todo app in your simulator or device.

So far LiteGap has only been tested with PhoneGap 2.9 and 3.0 apps. (ARC-enabled on iOS 6, and Android API level 11+) If you want to send pull requests, please modify [the code in this repo.](https://github.com/couchbaselabs/couchbase-lite-phonegap-plugin-builder)

## Architecture

This is where LiteGap fits in the picture:

![architecture.png](http://cl.ly/image/3b15030Y3f0q/couchbase-lite-phonegap-plugin-android.png)

_Note:_ your JavaScript code can also directly communicate with Couchbase Lite over a Javascript<->Native bridge, to [ask it what URL it has launched on for subsequent XHR access](https://github.com/couchbaselabs/LiteGap/blob/master/www/litegap-example.html)

_Note:_ Couchbase-Lite is capable of syncing with Couchbase Server or Apache CouchDB databases running in the cloud, as [shown here](https://github.com/couchbase/couchbase-lite-android)

# Where to go from here

There's an [example chat app with PhoneGap](https://github.com/couchbaselabs/CouchChat-PhoneGap) that illustrates the channel sync API. You can [read more about the app here](https://github.com/couchbaselabs/CouchChat-PhoneGap).

If you made it this far, you are now ready to build your custom PhoneGap App by editing the HTML, CSS, and Javascript files under the www directory.  Your same application code will work on both the iOS and Android platforms!

You might want to start with this [API reference](https://github.com/couchbase/couchbase-lite-ios/wiki/Guide%3A-REST) and this [API cheat sheet.](http://docs.couchdb.org/en/latest/api/reference.html) (For REST we use a 90% similar API as Apache CouchDB -- we'll have docs of our exact API in the next few months.)

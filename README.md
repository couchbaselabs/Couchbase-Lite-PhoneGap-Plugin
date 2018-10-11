# PhoneGap plugin for Couchbase Lite

Couchbase Lite is an embedded JSON database for occasionally connected devices. It syncs data in the background, so users can collaborate across devices. There is an event based `_changes` JSON feed API so you can drive data-binding UI frameworks like Sencha and Backbone to reflect remote updates interactively.

It works with native code as well as Cordova / PhoneGap on iOS and Android (you can even sync with Mac desktops), so it doesn't matter where your users are, they can work with the data, and as soon as they get back online, everyone will see their changes.

For instructions on using the plugin, see the [PhoneGap Getting Started](https://developer.couchbase.com/documentation/mobile/current/installation/phonegap/index.html) page.

## Architecture

This is where the plugin fits in the picture:

![architecture.png](http://cl.ly/image/3b15030Y3f0q/couchbase-lite-phonegap-plugin-android.png)

# Where to go from here

There's an [example chat app with PhoneGap](https://github.com/couchbaselabs/CouchChat-PhoneGap) that illustrates the channel sync API. You can [read more about the app here](https://github.com/couchbaselabs/CouchChat-PhoneGap).

If you made it this far, you are now ready to build your custom PhoneGap App by editing the HTML, CSS, and Javascript files under the www directory.  Your same application code will work on both the iOS and Android platforms!

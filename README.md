# LiteGap -- PhoneGap plugin for Couchbase Lite

Couchbase Lite is an embedded JSON database for occasionally connected devices. It syncs data in the background, so users can collaborate across devices. There is an [event based `_changes` JSON feed API](http://guide.couchdb.org/draft/notifications.html) so you can drive data-binding UI frameworks like Sencha and Backbone to reflect remote updates interactively.

It works with native code as well as PhoneGap on iOS and Android (you can even sync with Mac desktops), so it doesn't matter where your users are, they can work with the data, and as soon as they get back online, everyone will see their changes.

## Quick start

You install LiteGap into your PhoneGap app using [plugman](https://github.com/apache/cordova-plugman) and this command (where `$PLATFORM` is either `ios` or `android`):

```
plugman --platform $PLATFORM --project ~/MyPhonegapApp --plugin https://github.com/couchbaselabs/LiteGap.git
```

So far LiteGap has only been tested with PhoneGap 2.9 and 3.0 apps. (ARC-enabled on iOS 6, and Android ) If you want to send pull requests, please modify [the code in this repo.](https://github.com/couchbaselabs/couchbase-lite-phonegap-plugin-builder)

## Architecture

This is where LiteGap fits in the picture:

![architecture.png](http://cl.ly/image/3b15030Y3f0q/couchbase-lite-phonegap-plugin-android.png)

_Note:_ your JavaScript code can also directly communicate with Couchbase Lite over a Javascript<->Native bridge, to [ask it what URL it has launched on for subsequent XHR access](https://github.com/couchbaselabs/LiteGap/blob/master/www/litegap-example.html)

_Note:_ Couchbase-Lite is capable of syncing with Couchbase Server or Apache CouchDB databases running in the cloud, as [shown here](https://github.com/couchbase/couchbase-lite-android)

# Prerequisites

The following are required whether you are building an iOS or Android phonegap app.

* Install [Phonegap](http://phonegap.com/download/)
* Install [Plugman](https://github.com/apache/cordova-plugman)

# iOS Instructions

## Create iOS PhoneGap App

Follow the instructions on the [Phonegap iOS Platform Guide](http://docs.phonegap.com/en/2.9.0/guide_getting-started_ios_index.md.html#iOS%20Platform%20Guide) to create an empty iOS Phonegap app.

_Note:_ use the --arc flag to the `create` command if you are planning to create a project that uses ARC. (recommended)

## Install Plugin to app

```
plugman --platform ios --project ~/MyPhonegapApp --plugin https://github.com/couchbaselabs/LiteGap.git
```

You can rename your project's `www/litegap-example.html` to `index.html` at this point to verify your installation.

## Build Project via Xcode

* Open the Xcode project under ~/MyPhonegapApp in Xcode.

* Run the project

* It should look something like [this](http://cl.ly/image/3B2d243C003d/Screen%20Shot%202013-07-12%20at%202.15.53%20PM.png)

# Android Instructions

## Create Android PhoneGap App

Follow the instructions on the [Phonegap Android Platform Guide](http://docs.phonegap.com/en/2.9.0/guide_getting-started_android_index.md.html#Android%20Platform%20Guide) to create an empty Android Phonegap app.

The rest of the instructions will assume you've created your app in `~/MyPhonegapApp`

## Install Plugin to app

```
plugman --platform android --project ~/MyPhonegapApp --plugin https://github.com/couchbaselabs/LiteGap.git

```

You can rename your project's `www/litegap-example.html` to `index.html` at this point to verify your installation.

## Build Project via Eclipse

* Open ~/MyPhonegapApp in Eclipse.

* Build/run the project

* It should look something like [this](http://cl.ly/image/1O1v310s3Y3p/Screen%20Shot%202013-07-12%20at%2012.23.08%20PM.png).

# Where to go from here

If you made it this far, you are now ready to build your custom PhoneGap App by editing the HTML, CSS, and Javascript files under the www directory.  Your same application code will work on both the iOS and Android platforms!

You might want to start with this [API reference](https://github.com/couchbase/couchbase-lite-ios/wiki/Guide%3A-REST) and this [API cheat sheet.](http://docs.couchdb.org/en/latest/api/reference.html) (For REST we use a 90% similar API as Apache CouchDB -- we'll have docs of our exact API in the next few months.)

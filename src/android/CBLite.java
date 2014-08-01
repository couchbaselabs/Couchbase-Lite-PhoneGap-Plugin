package com.couchbase.cblite.phonegap;

import android.content.Context;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;

import com.couchbase.lite.android.AndroidContext;
import com.couchbase.lite.Manager;
import com.couchbase.lite.listener.LiteListener;
import com.couchbase.lite.listener.LiteServlet;
import com.couchbase.lite.listener.Credentials;
import com.couchbase.lite.router.URLStreamHandlerFactory;
import com.couchbase.lite.View;
import com.couchbase.lite.javascript.JavaScriptViewCompiler;
import com.couchbase.lite.util.Log;

import java.io.IOException;
import java.io.File;

public class CBLite extends CordovaPlugin {

	private static final int DEFAULT_LISTEN_PORT = 5984;
	private boolean initFailed = false;
	private int listenPort;
    private Credentials allowedCredentials;

	/**
	 * Constructor.
	 */
	public CBLite() {
		super();
		System.out.println("CBLite() constructor called");
	}

	public void initialize(CordovaInterface cordova, CordovaWebView webView) {
		System.out.println("initialize() called");

		super.initialize(cordova, webView);
		initCBLite();

	}

	private void initCBLite() {
		try {

		    allowedCredentials = new Credentials();

			URLStreamHandlerFactory.registerSelfIgnoreError();

			View.setCompiler(new JavaScriptViewCompiler());

			Manager server = startCBLite(this.cordova.getActivity());

			listenPort = startCBLListener(DEFAULT_LISTEN_PORT, server, allowedCredentials);

			System.out.println("initCBLite() completed successfully");


		} catch (final Exception e) {
			e.printStackTrace();
			initFailed = true;
		}

	}

	@Override
	public boolean execute(String action, JSONArray args,
			CallbackContext callback) {
		if (action.equals("getURL")) {
			try {

				if (initFailed == true) {
					callback.error("Failed to initialize couchbase lite.  See console logs");
					return false;
				} else {
					String callbackRespone = String.format(
							"http://%s:%s@localhost:%d/",
                            allowedCredentials.getLogin(),
                            allowedCredentials.getPassword(),
                            listenPort
                    );

					callback.success(callbackRespone);

					return true;
				}

			} catch (final Exception e) {
				e.printStackTrace();
				callback.error(e.getMessage());
			}
		}
		return false;
	}

	protected Manager startCBLite(Context context) {
		Manager manager;
		try {
		        Manager.enableLogging(Log.TAG, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_SYNC, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_QUERY, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_VIEW, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_CHANGE_TRACKER, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_BLOB_STORE, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_DATABASE, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_LISTENER, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_MULTI_STREAM_WRITER, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_REMOTE_REQUEST, Log.VERBOSE);
			Manager.enableLogging(Log.TAG_ROUTER, Log.VERBOSE);
			manager = new Manager(new AndroidContext(context), Manager.DEFAULT_OPTIONS);
			
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		return manager;
	}

	private int startCBLListener(int listenPort, Manager manager, Credentials allowedCredentials) {

		LiteListener listener = new LiteListener(manager, listenPort, allowedCredentials);
		int boundPort = listener.getListenPort();
		Thread thread = new Thread(listener);
		thread.start();
		return boundPort;

	}

	public void onResume(boolean multitasking) {
		System.out.println("CBLite.onResume() called");
	}

	public void onPause(boolean multitasking) {
		System.out.println("CBLite.onPause() called");
	}


}

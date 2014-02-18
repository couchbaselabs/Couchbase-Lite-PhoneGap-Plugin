package com.couchbase.cblite.phonegap;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;

import com.couchbase.lite.Manager;
import com.couchbase.lite.listener.LiteListener;
import com.couchbase.lite.router.URLStreamHandlerFactory;
import com.couchbase.lite.View;
import com.couchbase.lite.javascript.JavaScriptViewCompiler;

import java.io.IOException;
import java.io.File;

public class CBLite extends CordovaPlugin {

	private static final int DEFAULT_LISTEN_PORT = 5984;
	private boolean initFailed = false;
	private int listenPort;

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

			URLStreamHandlerFactory.registerSelfIgnoreError();

			View.setCompiler(new JavaScriptViewCompiler());

			File filesDir = this.cordova.getActivity().getFilesDir();
			Manager server = startCBLite(filesDir);

			listenPort = startCBLListener(DEFAULT_LISTEN_PORT, server);

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
							"http://localhost:%d/", listenPort);

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

	protected Manager startCBLite(File directory) {
		Manager server;
		try {
			server = new Manager(directory, Manager.DEFAULT_OPTIONS);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		return server;
	}

	private int startCBLListener(int listenPort, Manager server) {

		LiteListener listener = new LiteListener(server, listenPort);
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

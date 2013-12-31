package com.ironsource.kudoskit;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.util.Log;

import com.ironsrc.kudoskit.KudosKit;

public class CDVKudosKit extends CordovaPlugin
{
    private KudosKit mKudosKit = null;
    
    @Override
    public boolean execute(String action, JSONArray args, final CallbackContext callbackContext) throws JSONException
    {
        Log.v("KUDOS","got plugin command");
        if ( action.equals( "setup" ) )
        {
            String appKey = args.getString( 0 );
            JSONArray inApps = args.getJSONArray( 1 );
            this.setup( appKey, inApps, callbackContext );
            return true;
        }
        else if ( action.equals( "startRightSpot" ) )
        {
            final String name = args.getString( 0 );
            final boolean force = args.getBoolean( 1 );
            callbackContext.success( "ok" );
            cordova.getActivity().runOnUiThread(new Runnable() {
                public void run() {
                    startRightSpot( name, force );
                }
            });
            return true;
        }
        else if ( action.equals( "debug" ) )
        {
            this.debug( callbackContext );
            return true;
        }
        
        return false;
    }
    
    private void startRightSpot(String name, boolean force )
    {
        if (name != null && this.mKudosKit != null )
        {
        	this.mKudosKit.startRightspot( name, force ? KudosKit.START_ALWAYS : 0 );
        }
    }
    
    private void setup( final String appKey, JSONArray inApps, CallbackContext callbackContext )
    {
        if (appKey != null )
        {
            if( this.mKudosKit == null )
            {
            	final Activity  mainActivity = cordova.getActivity();
            	final String packageName = mainActivity.getPackageName();
                
                final String[] arr = new String[inApps.length()];
                for(int i = 0; i < inApps.length(); i++)
                {
                	try
                	{
                		arr[i] = inApps.getString(i);
                	}
                	catch( Exception e )
                	{
                		
                	}
                }
                
                callbackContext.success( "ok" );
                //cordova.getThreadPool().execute(new Runnable() {
                cordova.getActivity().runOnUiThread(new Runnable() {
                    public void run() {
                        mKudosKit = new KudosKit( mainActivity, packageName, appKey );
                        KudosKit.setQuiet( false );
                        mKudosKit.setup( new String[] {}, arr );
                        mKudosKit.onStart();
                    }
                });
                
            }
            else
            {
                callbackContext.error( "Setup was allredy called." );
            }
        }
        else
        {
            callbackContext.error( "Expected one non-empty string argument." );
        }
    }
    
    private void debug(CallbackContext callbackContext)
    {
        callbackContext.success( "ok" );
        if( this.mKudosKit != null )
    	{
            cordova.getActivity().runOnUiThread(new Runnable() {
                public void run() {
                	mKudosKit.debug();
                	
                }
            });
    	}
    }
    
}

KudosKit-PhoneGap
=================

KudosKit plugin for PhoneGap (Cordova)

# installing the plugin:

- cd to your app folder:

        cd my-app
    
- install using plugman: 

        plugman install --platform ios --project ./platforms/ios --plugin https://github.com/michaelbadichi/KudosKit-PhoneGap.git
        
        -or-
        
        plugman install --platform android --project ./platforms/android --plugin https://github.com/michaelbadichi/KudosKit-PhoneGap.git

# using the plugin:

- setup:

    kudoskit.setup( appKey, inAppsIdsArray )
    
        kudoskit.setup( '238328999', ['inapp1','inapp2','inapp3'] );
        
- showing rightspots:

    kudoskit.startRightSpot( rightspotName, forceShow )
    
        kudoskit.startRightSpot( 'Support Developers', true );
        
        kudoskit.startRightSpot( 'Game Over', false );
        
- debugging kit integration:

    kudoskit.debug()
    
        kudoskit.debug();
        
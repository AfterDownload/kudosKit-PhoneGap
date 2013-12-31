window.kudoskit = new function()
{
    this.setup = function( appid, inapps )
    {
        cordova.exec( function(sc){}, function(err){}, "CDVKudosKit", "setup", [appid, inapps] );
    };
    this.startRightSpot = function( name, force )
    {
        cordova.exec( function(sc){}, function(err){}, "CDVKudosKit", "startRightSpot", [name, force] );
    };
    this.debug = function()
    {
        cordova.exec( function(sc){}, function(err){}, "CDVKudosKit", "debug", [] );
    };
};
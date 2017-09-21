//
//  CoreGeoLocation.h
//  client
//
//  Created by Hussein Habibi on 6/19/1396 AP.
//  Copyright © Fall 2017 Adp Digital. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@protocol CoreGeoLocationDelegate <NSObject>

@required

/**
 * Invoked when new locations are available
 * @author AdpDigital co.
 *
 * locations is an array of CLLocation objects in chronological order.
 */
-(void) receivedLocationUpdates:(NSArray<CLLocation *> *_Nonnull) locations;

@optional

/**
 * Invoked when an error has occurred. Error types are defined in "CLError.h".
 */
-(void) geoLocationFailWithError:(NSError *_Nonnull)error;

/**
 * Invoked when the authorization status changes for this application.
 */
-(void) geoLocationAutorizationStatusChanged:(CLAuthorizationStatus)status;

@end

@interface CoreGeoLocation : NSObject <CLLocationManagerDelegate>

/**
 * Type for request authorization. WhileUseInApp or Always
 */
typedef enum {
    kWhileUseInApp = 0,
    kAlways = 1
} locationAutorizationEnumType;

/**
 *  allowsBackgroundLocationUpdates
 *
 *  Discussion:
 *      By default, this is NO for applications linked against iOS 9.0 or later,
 *      regardless of minimum deployment target.
 *
 *      With UIBackgroundModes set to include "location" in Info.plist, you must
 *      also set this property to YES at runtime whenever calling
 *      -startUpdatingLocation with the intent to continue in the background.
 *
 *      Setting this property to YES when UIBackgroundModes does not include
 *      "location" is a fatal error.
 *
 *      Resetting this property to NO is equivalent to omitting "location" from
 *      the UIBackgroundModes value.  Access to location is still permitted
 *      whenever the application is running (ie not suspended), and has
 *      sufficient authorization (ie it has WhenInUse authorization and is in
 *      use, or it has Always authorization).  However, the app will still be
 *      subject to the usual task suspension rules.
 *
 *      See -requestWhenInUseAuthorization and -requestAlwaysAuthorization for
 *      more details on possible authorization values.
 */
@property (nonatomic) BOOL allowBackgroundLocationUpdates __IOS_AVAILABLE(__IPHONE_9_0);

/**
 *	pausesLocationUpdatesAutomatically
 *
 *  Discussion:
 *		Specifies that location updates may automatically be paused when possible.
 *		By default, this is YES for applications linked against iOS 6.0 or later.
 */
@property (nonatomic) BOOL pausesAutomaticUpdate;

/**
 *  desiredAccuracy
 *
 *  Discussion:
 *      The desired location accuracy. The location service will try its best to achieve
 *      your desired accuracy. However, it is not guaranteed. To optimize
 *      power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *      use a large accuracy value when only a coarse location is needed). Use kCLLocationAccuracyBest to
 *      achieve the best possible accuracy. Use kCLLocationAccuracyBestForNavigation for navigation.
 *      The default value varies by platform.
 */
@property (nonatomic) CLLocationAccuracy desiredAccuracy;

/**
 *  distanceFilter
 *
 *  Discussion:
 *      Specifies the minimum update distance in meters. Client will not be notified of movements of less
 *      than the stated value, unless the accuracy has improved. Pass in kCLDistanceFilterNone to be
 *      notified of all movements. By default, kCLDistanceFilterNone is used.
 */
@property (nonatomic) CLLocationDistance distanceFilter;

/**
 *	activityType
 *
 *  Discussion:
 *		Specifies the type of user activity. Currently affects behavior such as
 *		the determination of when location updates may be automatically paused.
 *		By default, CLActivityTypeOther is used.
 */
@property (nonatomic) CLActivityType activityType;

/**
 * lastLocation
 *
 * Discussion:
 *      Get the last received location. Can be nil if no location has been received.
 */
@property (nonatomic,strong) CLLocation * _Nullable lastLocation;

/**
 * locationAutorization
 *
 * Discussion:
 *      Set autorization type before calling startLocationUpdate method.
 *      By default set Always.
 */
@property (nonatomic) locationAutorizationEnumType locationAutorization;

/**
 * isUserWasAutorizeLocation
 *
 * Discussion:
 *      Check user press allow for autorization or denied.
 */
@property (nonatomic, readonly) BOOL isUserWasAutorizeLocation;

/**
 * isMonitoringSignificantLocationChangesStarted
 *
 * Discussion:
 *      Check startMonitoringSignificantLocationChanges was started or stopped.
 */
@property (nonatomic,readonly) BOOL isMonitoringSignificantLocationChangesStarted;

/**
 * Singletone of coreGeoLocation
 */
+(instancetype _Nonnull ) sharedInstance;

/**
 *  Init with Always Autorization.
 */
-(instancetype _Nonnull ) init;

/**
 * Init with locationAutorizationType (WhileUseInApp or Always).
 *
 * @author AdpDigital co.
 *
 * @param autorizationType 2 state, WhileUseInApp or Always
 */
-(instancetype _Nonnull ) initWithAutorization:(locationAutorizationEnumType) autorizationType;

/**
 * @description addDelegate method purpose for multi delegation and callback support,
 * and add new delegate object in delegate objects list
 * @see -CoreGeoLocationDelegate
 *
 * return void
 */
-(void) addDelegate:(id<CoreGeoLocationDelegate>) delegate;

/**
 * Start location tracking, First check location manager was enabled and after that
 * start tracking location
 * @author AdpDigital co.
 *
 * @return Location manager is enable to start or not.
 */
- (void) startLocationUpdate;

/**
 * Stop location tracking.
 * @author AdpDigital co.
 */
- (void) stopLocationUpdate;

/**
 * Start monitoring significant location changes. This method invoke 
 *          receivedLocationUpdates:locations when app was terminated or suspended.
 * @author AdpDigital co.
 */
- (void) startMonitoringSignificantLocationChanges;

/**
 * Stop monitoring significant location changes
 * @author AdpDigital co.
 */
- (void) stopMonitoringSignificantLocationChanges;

/*
 *  requestSingleLocation:(locationCallBack)
 *
 * @author AdpDigital co.
 *  Discussion:
 *      Request a single location update.
 *
 *      The service will attempt to determine location with accuracy according
 *      to the desiredAccuracy property.  The location update will be delivered
 *      via the standard delegate callback.
 *
 *      If the best available location has lower accuracy, then it will be
 *      delivered via the standard delegate callback after timeout.
 *
 *      If no location can be determined, the geoLocationFailWithError:error
 *      delegate callback will be delivered with error location unknown.
 */
- (void) requestSingleLocation: (void(^_Nullable)( CLLocation * _Nullable )) locationCallBack;

@end

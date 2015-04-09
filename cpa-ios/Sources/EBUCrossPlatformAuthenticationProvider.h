//
//  Copyright (c) European Broadcasting Union. All rights reserved.
//
//  Licence information is available from the LICENCE file.
//

#import "EBUToken.h"

#import <Foundation/Foundation.h>

/**
 * Authentication error codes
 */
typedef NS_ENUM(NSInteger, EBUAuthenticationErrorCode) {
    EBUAuthenticationErrorUnknown,                  // An unknown error has occurred
    EBUAuthenticationErrorInvalidRequest,           // The request is invalid
    EBUAuthenticationErrorInvalidClient,            // The client is invalid
    EBUAuthenticationErrorTooFast,                  // Requests are made too fast. Slow down
    EBUAuthenticationErrorPendingAuthorization      // Authorization has not yet been made
};

/**
 * Common domain of authentication errors
 */
OBJC_EXPORT NSString * const EBUAuthenticationErrorDomain;

/**
 * Manage cross-platform authentication (CPA) with an authorization provider.
 *
 * For more information about CPA, refer to https://tech.ebu.ch/docs/tech/tech3366.pdf
 *
 * An authorization provider delivers tokens associating applications with an identity. Two modes are available:
 *   - client mode (unauthenticated association): An anonymous identity is created and the application is associated with it
 *   - user mode (authenticated associated): The application is linked with a user account, which requires the user to log in
 *
 * When an application has been successfully associated, a token is retrieved and stored in the keychain. This token can then
 * be used to access other services on behalf of the identity.
 *
 * Usually, tokens must be retrieved by calling the method -tokenForDomain:withCompletionBlock:, except when your user
 * needs to be able to link its account with the application. In such cases, call -userTokenForDomain:withCompletionBlock:
 * instead
 *
 * You can instantiate as many providers as required. In most cases a single provider should suffice, which you can 
 * instantiate and install as default provider by calling +setDefaultCrossPlatformAuthenticationProvider:
 *
 * This authentication provider is intended to be used from the main application thread. Using it from other threads
 * results in undefined behavior.
 */
@interface EBUCrossPlatformAuthenticationProvider : NSObject

/**
 * Set the default authentication provider, returning the previously installed one (if any)
 */
+ (EBUCrossPlatformAuthenticationProvider *)setDefaultAuthenticationProvider:(EBUCrossPlatformAuthenticationProvider *)authenticationProvider;

/**
 * Return the currently set authentication provider, nil if none
 */
+ (instancetype)defaultAuthenticationProvider;

/**
 * Create an authentication provider connecting to the specified authorization provider URL (mandatory)
 */
- (instancetype)initWithAuthorizationProviderURL:(NSURL *)authorizationProviderURL NS_DESIGNATED_INITIALIZER;

/**
 * The associated authorization provider URL
 */
@property (nonatomic, readonly) NSURL *authorizationProviderURL;

/**
 * Return the token locally available for a given domain, nil if none
 */
- (EBUToken *)tokenForDomain:(NSString *)domain;

/**
 * Retrieve a token for the specified domain, authenticated or not. Before calling this method, you should check whether a
 * an appropriate token is locally already available by calling -tokenForDomain: method first.
 *
 * If the request token must be authenticated, the user will be redirected to a verification URL to enter her credentials
 *
 * If a token request is performed while a token is already available locally, and if the request is successful, the
 * old token will be discarded.
 */
- (void)requestTokenForDomain:(NSString *)domain authenticated:(BOOL)authenticated withCompletionBlock:(void (^)(EBUToken *token, NSError *error))completionBlock;

/**
 * Discard a locally available token for the given domain, if any
 */
- (void)discardTokenForDomain:(NSString *)domain;

@end

@interface EBUCrossPlatformAuthenticationProvider (UnavailableMethods)

- (instancetype)init NS_UNAVAILABLE;

@end

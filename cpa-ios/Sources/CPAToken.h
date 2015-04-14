//
//  Copyright (c) European Broadcasting Union. All rights reserved.
//
//  Licence information is available from the LICENCE file.
//

#import <Foundation/Foundation.h>

/**
 * Token type
 */
typedef NS_ENUM(NSInteger, CPATokenType) {
    CPATokenTypeClient,                 // Client token (unauthenticated)
    CPATokenTypeUser                    // User token (authenticated)
};

/**
 * Service token
 */
NS_ASSUME_NONNULL_BEGIN
@interface CPAToken : NSObject <NSCoding>

/**
 * The token string
 */
@property (nonatomic, readonly, copy) NSString *value;

/**
 * The client identifier for which the token was requested
 */
@property (nonatomic, readonly, copy) NSString *clientIdentifier;

/**
 * The client secret
 */
@property (nonatomic, readonly, copy) NSString *clientSecret;

/**
 * The domain to which the token is associated
 */
@property (nonatomic, readonly, copy) NSString *domain;

/**
 * The friendly domain name
 */
@property (nonatomic, readonly, copy, nullable) NSString *domainName;

/**
 * The token type
 */
@property (nonatomic, readonly) CPATokenType type;

/**
 * Lifetime of the token in seconds
 */
@property (nonatomic, readonly) NSInteger lifetimeInSeconds;

@end

@interface CPAToken (UnavailableMethods)

- (instancetype)init NS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END
//
//  Copyright (c) European Broadcasting Union. All rights reserved.
//
//  Licence information is available from the LICENCE file.
//

#import <Foundation/Foundation.h>

/**
 * Token type
 */
typedef NS_ENUM(NSInteger, EBUTokenType) {
    EBUTokenTypeClient,                 // Client token (unauthenticated)
    EBUTokenTypeUser                    // User token (authenticated)
};

/**
 * Service token
 */
@interface EBUToken : NSObject <NSCoding>

/**
 * The token string
 */
@property (nonatomic, readonly, copy) NSString *value;

/**
 * The domain to which the token is associated
 */
@property (nonatomic, readonly, copy) NSString *domain;

/**
 * The friendly domain name
 */
@property (nonatomic, readonly, copy) NSString *domainName;

/**
 * The token type
 */
@property (nonatomic, readonly) EBUTokenType type;

/**
 * Lifetime of the token in seconds
 */
@property (nonatomic, readonly) NSInteger lifetimeInSeconds;

@end

@interface EBUToken (UnavailableMethods)

- (instancetype)init NS_UNAVAILABLE;

@end

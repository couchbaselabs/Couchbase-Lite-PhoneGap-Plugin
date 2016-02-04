//
//  CBLView.h
//  CouchbaseLite
//
//  Created by Jens Alfke on 6/19/12.
//  Copyright (c) 2012-2013 Couchbase, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
@class CBLDatabase, CBLQuery;

#if __has_feature(nullability) // Xcode 6.3+
#pragma clang assume_nonnull begin
#else
#define nullable
#define __nullable
#define __nonnull
#endif


typedef enum {
    kCBLMapReduceIndex = 1, /**< Regular map/reduce index with JSON keys. */
    kCBLFullTextIndex,  /**< Keys must be strings and will be indexed by the words they contain. */
    kCBLGeoIndex        /**< Geo-query index; not supported yet. */
} CBLViewIndexType;


typedef void (^CBLMapEmitBlock)(id key, __nullable id value);


/** A "map" function called when a document is to be added to a view.
    @param doc  The contents of the document being analyzed.
    @param emit  A block to be called to add a key/value pair to the view. Your block can call it zero, one or multiple times. */
typedef void (^CBLMapBlock)(CBLJSONDict* doc, CBLMapEmitBlock emit);

/** A "reduce" function called to summarize the results of a view.
	@param keys  An array of keys to be reduced (or nil if this is a rereduce).
	@param values  A parallel array of values to be reduced, corresponding 1::1 with the keys.
	@param rereduce  YES if the input values are the results of previous reductions.
	@return  The reduced value; almost always a scalar or small fixed-size object. */
typedef __nonnull id (^CBLReduceBlock)(NSArray* __nonnull keys,
                                       NSArray* __nonnull values,
                                       BOOL rereduce);


#define MAPBLOCK(BLOCK) ^(CBLJSONDict* doc, void (^emit)(id key, id value)){BLOCK}
#define REDUCEBLOCK(BLOCK) ^id(NSArray* keys, NSArray* values, BOOL rereduce){BLOCK}


/** Returns a special value that, when emitted as a key, causes the given text to be indexed with
    the full-text indexer. Used inside a map block, like so: `emit(CBLTextKey(longText), value);` */
FOUNDATION_EXTERN id CBLTextKey(NSString* text);

/** An external object that knows how to map source code of some sort into executable functions. */
@protocol CBLViewCompiler <NSObject>
- (nullable CBLMapBlock) compileMapFunction: (NSString*)mapSource language: (NSString*)language;
- (nullable CBLReduceBlock) compileReduceFunction: (NSString*)reduceSource
                                         language: (NSString*)language;
@end


/** A "view" in a CouchbaseLite database -- essentially a persistent index managed by map/reduce.
    The view can be queried using a CBLQuery. */
@interface CBLView : NSObject

/** The database that owns this view. */
@property (readonly) CBLDatabase* database;

/** The name of the view. */
@property (readonly) NSString* name;

/** The map function that controls how index rows are created from documents. */
@property (readonly, nullable) CBLMapBlock mapBlock;

/** The optional reduce function, which aggregates together multiple rows. */
@property (readonly, nullable) CBLReduceBlock reduceBlock;

/** Defines a view's functions.
    The view's definition is given as an Objective-C block (or NULL to delete the view). The body of the block should call the 'emit' block (passed in as a paramter) for every key/value pair it wants to write to the view.
    Since the function itself is obviously not stored in the database (only a unique string identifying it), you must re-define the view on every launch of the app! If the database needs to rebuild the view but the function hasn't been defined yet, it will fail and the view will be empty, causing weird problems later on.
    It is very important that this block be a law-abiding map function! As in other languages, it must be a "pure" function, with no side effects, that always emits the same values given the same input document. That means that it should not access or change any external state; be careful, since blocks make that so easy that you might do it inadvertently!
    The block may be called on any thread, or on multiple threads simultaneously. This won't be a problem if the code is "pure" as described above, since it will as a consequence also be thread-safe. 
    @param mapBlock  The map function. The MAPBLOCK macro makes it easier to declare this.
    @param reduceBlock  The reduce function, or nil for none. The REDUCEBLOCK macro makes it easier to declare this.
    @param version  An arbitrary string that will be stored persistently along with the index. Usually a string literal like @"1". If you subsequently change the functionality of the map or reduce function, change this string as well: the call will detect that it's different and will clear the index so it can be rebuilt by the new function.
    @return  YES if the view was updated and the index cleared; NO if the version stayed the same. */
- (BOOL) setMapBlock: (CBLMapBlock)mapBlock
         reduceBlock: (nullable CBLReduceBlock)reduceBlock
             version: (NSString*)version;

/** Defines a view that has no reduce function.
    See -setMapBlock:reduceBlock:version: for more details. */
- (BOOL) setMapBlock: (CBLMapBlock)mapBlock
             version: (NSString*)version;

/** If this property is set, only documents whose "type" property is equal to its value will be
    passed to the map block and indexed. This can speed up indexing.
    Just like the map block, this property is not persistent; it needs to be set at runtime before
    the view is queried. And if its value changes, the view's version also needs to change. */
@property (copy) NSString* documentType;

/** Is the view's index currently out of date? */
@property (readonly) BOOL stale;

/** The last sequence number indexed so far. */
@property (readonly) SInt64 lastSequenceIndexed;

/** Total number of rows in the view. The view's index will be updated if needed before returning
    the totalRows value. */
@property (readonly) NSUInteger totalRows;

/** Deletes the view's persistent index. It will be regenerated on the next query. */
- (void) deleteIndex;

/** Deletes the view, persistently. */
- (void) deleteView;

/** Creates a new query object for this view. The query can be customized and then executed. */
- (CBLQuery*) createQuery;

/** Utility function to use in reduce blocks. Totals an array of NSNumbers. */
+ (NSNumber*) totalValues: (NSArray*)values;

/** Registers an object that can compile map/reduce functions from source code. */
+ (void) setCompiler: (nullable id<CBLViewCompiler>)compiler;

/** The registered object, if any, that can compile map/reduce functions from source code. */
+ (nullable id<CBLViewCompiler>) compiler;

- (instancetype) init NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END

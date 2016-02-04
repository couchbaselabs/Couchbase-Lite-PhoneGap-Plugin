//
//  CBLRevision.h
//  CouchbaseLite
//
//  Created by Jens Alfke on 6/17/12.
//  Copyright (c) 2012-2013 Couchbase, Inc. All rights reserved.
//

#import "CBLBase.h"
@class CBLDocument, CBLDatabase, CBLAttachment, CBLSavedRevision, CBLUnsavedRevision;

NS_ASSUME_NONNULL_BEGIN

/** A revision of a CBLDocument.
    This is the abstract base class of CBLSavedRevision (existing revisions) and CBLNewRevision
    (revisions yet to be saved). */
@interface CBLRevision : NSObject

/** The document this is a revision of. */
@property (readonly, weak) CBLDocument* document;

/** The database this revision's document belongs to. */
@property (readonly) CBLDatabase* database;

/** Does this revision mark the deletion of its document?
    (In other words, does it have a "_deleted" property?) */
@property (readonly) BOOL isDeletion;

/** Does this revision mark the deletion or removal (from available channels) of its document ?
    (In other words, does it have a "_deleted_ or "_removed" property?) */
@property (readonly) BOOL isGone;

/** The ID of this revision. Will be nil if this is an unsaved CBLNewRevision. */
@property (readonly, nullable) NSString* revisionID;

/** The revision this one is a child of. */
@property (readonly, nullable) CBLSavedRevision* parentRevision;

/** The ID of the parentRevision. */
@property (readonly, nullable) NSString* parentRevisionID;

/** Returns the ancestry of this revision as an array of CBLRevisions, in chronological order.
    Older revisions are NOT guaranteed to have their properties available. */
- (nullable CBLArrayOf(CBLRevision*)*) getRevisionHistory: (NSError**)outError;

/** The revision's contents as parsed from JSON.
    Keys beginning with "_" are defined and reserved by CouchbaseLite; others are app-specific.
    The first call to this method may need to fetch the properties from disk, but subsequent calls
    are very cheap. */
@property (readonly, nullable) CBLJSONDict* properties;

/** The user-defined properties, without the ones reserved by CouchbaseLite.
    This is based on -properties, with every key whose name starts with "_" removed. */
@property (readonly, copy, nullable) CBLJSONDict* userProperties;

/** Shorthand for [self.properties objectForKey: key]. */
- (nullable id) propertyForKey: (NSString*)key;

/** Same as -propertyForKey:. Enables "[]" access in Xcode 4.4+ */
- (nullable id) objectForKeyedSubscript: (NSString*)key;

#pragma mark ATTACHMENTS

/** The names of all attachments (an array of strings). */
@property (readonly, nullable) CBLArrayOf(NSString*)* attachmentNames;

/** Looks up the attachment with the given name (without fetching its contents yet). */
- (nullable CBLAttachment*) attachmentNamed: (NSString*)name;

/** All attachments, as CBLAttachment objects. */
@property (readonly, nullable) CBLArrayOf(CBLAttachment*)* attachments;

- (instancetype) init NS_UNAVAILABLE;

@end



/** An existing revision of a CBLDocument. Most of its API is inherited from CBLRevisionBase. */
@interface CBLSavedRevision : CBLRevision

/** Are this revision's properties available? They may not be if the revision is an ancestor and
    either the database has been compacted, or the revision was replicated from another db. */
@property (readonly) BOOL propertiesAvailable;

/** Creates a new mutable child revision whose properties and attachments are initially identical
    to this one's, which you can modify and then save. */
- (CBLUnsavedRevision*) createRevision;

/** Creates and saves a new revision with the given properties.
    This will fail with a 412 error if the receiver is not the current revision of the document. */
- (nullable CBLSavedRevision*) createRevisionWithProperties: (nullable CBLJSONDict*)properties
                                                      error: (NSError**)outError;

/** Deletes the document by creating a new deletion-marker revision. */
- (nullable CBLSavedRevision*) deleteDocument: (NSError**)outError;

@end



/** An unsaved new revision. Most of its API is inherited from CBLRevisionBase. */
@interface CBLUnsavedRevision : CBLRevision

// These properties are overridden to be settable:
@property (readwrite) BOOL isDeletion;
@property (readwrite, copy, nullable) NSMutableDictionary* properties;
@property (readwrite, copy, nullable) CBLJSONDict* userProperties;
- (void) setObject: (nullable id)object forKeyedSubscript: (NSString*)key;

/** Saves the new revision to the database.
    This will fail with a 412 error if its parent (the revision it was created from) is not the current revision of the document.
    Afterwards you should use the returned CBLSavedRevision instead of this object.
    @return  A new CBLSavedRevision representing the saved form of the revision. */
- (nullable CBLSavedRevision*) save: (NSError**)outError;

/** A special variant of -save: that always adds the revision, even if its parent is not the
    current revision of the document.
    This can be used to resolve conflicts, or to create them. If you're not certain that's what you
    want to do, you should use the regular -save: method instead. */
- (nullable CBLSavedRevision*) saveAllowingConflict: (NSError**)outError;

/** Creates, updates or deletes an attachment.
    The attachment data will be written to the database when the revision is saved.
    @param name  The attachment name. By convention, this looks like a filename.
    @param mimeType  The MIME type of the content.
    @param content  The body of the attachment, or nil to remove the attachment. */
- (void) setAttachmentNamed: (NSString*)name
            withContentType: (nullable NSString*)mimeType
                    content: (nullable NSData*)content;

/** Creates, updates or deletes an attachment whose body comes from a file.
    (The method takes a URL, but it must be a "file:" URL. Remote resources are not supported.)
    The file need only be readable. It won't be moved or altered in any way.
    The attachment data will be copied from the file into the database when the revision is saved.
    The file needs to be preserved until then, but afterwards it can safely be deleted.
    @param name  The attachment name. By convention, this looks like a filename.
    @param mimeType  The MIME type of the content.
    @param fileURL  The URL of a local file whose contents should be copied into the attachment. */
- (void) setAttachmentNamed: (NSString*)name
            withContentType: (nullable NSString*)mimeType
                 contentURL: (nullable NSURL*)fileURL;

/** Removes the attachment with the given name.
    When this revision is saved, it won't include the attachment. However, the attachment will
    still be present in the parent revision, until the database is next compacted. */
- (void) removeAttachmentNamed: (NSString*)name;

@end


NS_ASSUME_NONNULL_END

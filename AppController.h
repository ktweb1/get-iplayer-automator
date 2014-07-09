//
//  AppController.h
//  Get_iPlayer GUI
//
//  Created by Thomas Willson on 7/10/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "BBCDownload.h"
#import "Series.h"
#import "ITVDownload.h"
#import "Download.h"
#import <IOKit/pwr_mgt/IOPMLib.h>
#import "NilToStringTransformer.h"

@interface AppController : NSObject {
	//General
	NSString *getiPlayerPath;
	NSString *noWarningArg;
	NSString *profileDirArg;
	NSString *listFormat;
	NSString *currentTypeArgument;
	IBOutlet NSWindow *mainWindow;
	IBOutlet NSApplication *application;
   IBOutlet NSWindow *historyWindow;
   IOPMAssertionID powerAssertionID;
	
	//Log Components
	IBOutlet NSTextView *log;
	IBOutlet NSWindow *logWindow;
	IBOutlet NSScrollView *logScroll;
	NSMutableAttributedString *log_value;
	
	//Update Components
	NSTask *getiPlayerUpdateTask;
	NSPipe *getiPlayerUpdatePipe;
	NSArray *getiPlayerUpdateArgs;
   NSMutableArray *typesToCache;
	BOOL didUpdate;
	BOOL runSinceChange;
   BOOL quickUpdateFailed;
   NSUInteger nextToCache;
   NSDictionary *updateURLDic;
   NSDate *lastUpdate;
	
	//Main Window: Search
	IBOutlet NSTextField *searchField;
	IBOutlet NSProgressIndicator *searchIndicator;
	IBOutlet NSArrayController *resultsController;
   IBOutlet NSTableView *searchResultsTable;
	NSMutableArray *searchResultsArray;
	NSTask *searchTask;
	NSPipe *searchPipe;
	NSMutableString *searchData;
	
	//PVR
	IBOutlet NSTextField *pvrSearchField;
	IBOutlet NSProgressIndicator *pvrSearchIndicator;
	IBOutlet NSArrayController *pvrResultsController;
	IBOutlet NSArrayController *pvrQueueController;
   IBOutlet NSPanel *pvrPanel;
	NSMutableArray *pvrSearchResultsArray;
	NSTask *pvrSearchTask;
	NSPipe *pvrSearchPipe;
	NSMutableString *pvrSearchData;
	NSMutableArray *pvrQueueArray;
	
	//Queue
	IBOutlet NSButton *addToQueue;
	IBOutlet NSArrayController *queueController;
	IBOutlet NSButton *getNamesButton;
	NSMutableArray *queueArray;
	IBOutlet NSTableView *queueTableView;
	
	//Main Window: Status
	IBOutlet NSProgressIndicator *overallIndicator;
	IBOutlet NSProgressIndicator *currentIndicator;
	IBOutlet NSTextField *overallProgress;
	IBOutlet NSTextField *currentProgress;
	
	//Download Controller
	Download *currentDownload;
	IBOutlet NSToolbarItem *stopButton;
	IBOutlet NSToolbarItem *startButton;
	
	//Preferences
	NSMutableArray *tvFormatList;
	NSMutableArray *radioFormatList;
   NSMutableArray *itvFormatList;
	IBOutlet NSArrayController *tvFormatController;
	IBOutlet NSArrayController *radioFormatController;
   IBOutlet NSArrayController *itvFormatController;
   IBOutlet NSButton *itvTVCheckbox;
   IBOutlet NSPanel *prefsPanel;
   IBOutlet NSButton *ch4TVCheckbox;
   
	//Scheduling a Start
	IBOutlet NSPanel *scheduleWindow;
	IBOutlet NSDatePicker *datePicker;
	NSTimer *interfaceTimer;
	NSTimer *scheduleTimer;
	BOOL runScheduled;
	
	//Live TV
	IBOutlet NSWindow *liveTVWindow;
	IBOutlet NSArrayController *liveTVChannelController;
	IBOutlet NSTableView *liveTVTableView;
	IBOutlet NSButton *liveStart;
	IBOutlet NSButton *liveStop;
	NSTask *getiPlayerStreamer;
	NSTask *mplayerStreamer;
	NSPipe *liveTVPipe;
	NSPipe *liveTVError;
   
   //Download Solutions
   IBOutlet NSWindow *solutionsWindow;
   IBOutlet NSArrayController *solutionsArrayController;
   IBOutlet NSTableView *solutionsTableView;
   NSDictionary *solutionsDictionary;
   
   //Proxy
   HTTPProxy *proxy;
   NSMutableDictionary *proxyDict;
   enum {
      kProxyLoadCancelled = 1,
      kProxyLoadFailed = 2,
      kProxyTestFailed = 3
   };
   
   
   //PVR list editing
   NilToStringTransformer *nilToEmptyStringTransformer;
   NilToStringTransformer *nilToAsteriskTransformer;
   
   //Verbose Logging
   BOOL verbose;
   
   //Extended Show Information
   IBOutlet NSProgressIndicator *retrievingInfoIndicator;
   IBOutlet NSTextField *loadingLabel;
   IBOutlet NSView *loadingView;
   IBOutlet NSView *infoView;
   IBOutlet NSPopover *popover;
   IBOutlet NSImageView *imageView;
   IBOutlet NSTextField *seriesNameField;
   IBOutlet NSTextField *episodeNameField;
   IBOutlet NSTextField *numbersField;
   IBOutlet NSTextField *durationField;
   IBOutlet NSTextField *categoriesField;
   IBOutlet NSTextField *firstBroadcastField;
   IBOutlet NSTextField *lastBroadcastField;
   IBOutlet NSTextView *descriptionView;
   IBOutlet NSDictionaryController *modeSizeController;
   IBOutlet NSTextField *typeField;
}

//Proxy
- (void)loadProxyInBackgroundForSelector:(SEL)selector withObject:(id)object;

//Update
- (void)getiPlayerUpdateFinished;
- (IBAction)updateCache:(id)sender;
- (IBAction)forceUpdate:(id)sender;
- (void)updateCacheForType:(NSString *)type;
//Log Components
- (IBAction)showLog:(id)sender;
- (IBAction)copyLog:(id)sender;
- (void)addToLog:(NSString *)string :(id)sender;
- (void)addToLog:(NSString *)string;

//Search
- (IBAction)pvrSearch:(id)sender;
- (IBAction)mainSearch:(id)sender;

//PVR
- (IBAction)addToAutoRecord:(id)sender;

//Misc.
- (void)addToiTunesThread:(Programme *)show;
- (void)cleanUpPath:(Programme *)show;
- (void)seasonEpisodeInfo:(Programme *)show;
- (IBAction)chooseDownloadPath:(id)sender;
- (IBAction)restoreDefaults:(id)sender;
- (IBAction)showFeedback:(id)sender;
- (IBAction)closeWindow:(id)sender;
+ (AppController*)sharedController;

//Queue
- (IBAction)addToQueue:(id)sender;
- (IBAction)getName:(id)sender;
- (void)getNameForProgramme:(Programme *)pro;
- (void)processGetNameData:(NSString *)getNameData forProgramme:(Programme *)p;
- (IBAction)getCurrentWebpage:(id)sender;
- (void)setQueueArray:(NSArray *)queue;
- (NSArray *)queueArray;
- (IBAction)removeFromQueue:(id)sender;

//Arguments
- (NSString *)typeArgument:(id)sender;
- (NSString *)cacheExpiryArgument:(id)sender;
- (IBAction)typeChanged:(id)sender;

//Download Controller
- (IBAction)startDownloads:(id)sender;
- (IBAction)stopDownloads:(id)sender;

//PVR
- (IBAction)addSeriesLinkToQueue:(id)sender;
- (BOOL)processAutoRecordData:(NSString *)autoRecordData2 forSeries:(Series *)series2;
- (IBAction)hidePvrShow:(id)sender;

//Scheduling a Start
- (IBAction)showScheduleWindow:(id)sender;
- (IBAction)scheduleStart:(id)sender;
- (IBAction)cancelSchedule:(id)sender;

//Live TV
- (IBAction)showLiveTVWindow:(id)sender;
- (IBAction)startLiveTV:(id)sender;
- (IBAction)stopLiveTV:(id)sender;

//Extended Show Information
- (IBAction)showExtendedInformationForSelectedProgramme:(id)sender;
- (void)loadProxyInBackgroundForSelector:(SEL)selector withObject:(id)object onTarget:(id)target;


//Download Solutions
//- (IBAction)saveSolutionsAsText:(id)sender;

//Key-Value Coding
@property (readwrite) NSMutableAttributedString *log_value;
@property (readonly) NSString *getiPlayerPath;
@property (readonly) HTTPProxy *proxy;

@end

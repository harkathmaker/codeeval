// https://www.codeeval.com/open_challenges/54/

/*Objective-C programs are executed via GNUStep on Linux*/

#import <Foundation/Foundation.h>

@interface CashRegister : NSObject
{
    NSArray *denominations;
    NSArray *denomValues;
}

// Returns a comma-separated string of denominations needed as change.
// Take a semicolon-separated string in the format "15.94;16.00"
-(NSString*) getChangeForExchange:(NSString*)exchg;
// Returns a comma-separated string of all denominations needed as change.
// price and cash are given in cents.
-(NSString*) getChangeForPrice:(int)price givenCash:(int)cash;
@end

@implementation CashRegister
-(id) init {
    if(self = [super init]) {
        denominations = [[NSArray alloc] initWithObjects:@"ONE HUNDRED",
                                         @"FIFTY",@"TWENTY",@"TEN",@"FIVE",
                                         @"TWO",@"ONE",@"HALF DOLLAR",
                                         @"QUARTER",@"DIME",@"NICKEL",
                                         @"PENNY",nil];
        denomValues = [[NSArray alloc] initWithObjects:
                                        [NSNumber numberWithInt:10000],
                                        [NSNumber numberWithInt:5000],
                                        [NSNumber numberWithInt:2000],
                                        [NSNumber numberWithInt:1000],
                                        [NSNumber numberWithInt:500],
                                        [NSNumber numberWithInt:200],
                                        [NSNumber numberWithInt:100],
                                        [NSNumber numberWithInt:50],
                                        [NSNumber numberWithInt:25],
                                        [NSNumber numberWithInt:10],
                                        [NSNumber numberWithInt:5],
                                        [NSNumber numberWithInt:1],
                                        nil];
                                                        
    }
    return self;
}

-(NSString*) getChangeForExchange:(NSString*)exchg {
    NSArray *components = [exchg componentsSeparatedByString:@";"];
    int price = (int)(((NSString*)[components objectAtIndex:0]).doubleValue * 100);
    int cash = (int)(((NSString*)[components objectAtIndex:1]).doubleValue * 100);
    return [self getChangeForPrice:price givenCash:cash];
}

-(NSString*) getChangeForPrice:(int)price givenCash:(int)cash {
    if(price > cash) {
        return @"ERROR";
    } else if(price == cash) {
        return @"ZERO";
    } else {
        NSString *ret = [NSString string];
        int k = 0;
        cash -= price;
        while(cash > 0) {
            int val = ((NSNumber*)[denomValues objectAtIndex:k]).intValue;
            if(cash >= val) {
                cash -= val;
                ret = [ret stringByAppendingString:[denominations objectAtIndex:k]];
                if(cash > 0) {
                    ret = [ret stringByAppendingString:@","];
                }
            } else {
                k++;
            }
        }
        return ret;
    }
}

-(void) dealloc {
    [denominations release];
    [denomValues release];
    [super dealloc];
}
@end

int main (int argc, const char * argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    // read filename from the first argument
    NSString* filename = [NSString stringWithCString:argv[1] encoding:NSASCIIStringEncoding];
    NSString* content = [NSString stringWithContentsOfFile:filename encoding:NSASCIIStringEncoding error:nil];
    NSScanner* scanner = [NSScanner scannerWithString:content];

    CashRegister *cr = [[CashRegister alloc] init];
      
    while (![scanner isAtEnd]) {
        NSString* line;
        [scanner scanUpToString:@"\n" intoString:&line];
        
        // output an answer
        printf("%s\n",[[cr getChangeForExchange:line] UTF8String]);
    }
    [cr release];
    
    [pool release];
    return 0;
}

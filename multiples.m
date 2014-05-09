// https://www.codeeval.com/open_challenges/18/

/*Objective-C programs are executed via GNUStep on Linux*/

#import <Foundation/Foundation.h>

@interface MultipleFinder : NSObject
{
    int x;
    int n;
}

-(void) assignNums:(NSString*)s;
-(int) nextMultiple;
@end

@implementation MultipleFinder
-(void) assignNums:(NSString*)s {
    NSArray *array = [s componentsSeparatedByString:@","];
    x = ((NSString*)[array objectAtIndex:0]).intValue;
    n = ((NSString*)[array objectAtIndex:1]).intValue;
}

-(int) nextMultiple {
    int r = n;
    while(r < x) {
        r *= 2;
    }
    while(r >= x) {
        r -= n;
    }
    return r + n;
}

@end

int main (int argc, const char * argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    // read filename from the first argument
    NSString* filename = [NSString stringWithCString:argv[1] encoding:NSASCIIStringEncoding];
    NSString* content = [NSString stringWithContentsOfFile:filename encoding:NSASCIIStringEncoding error:nil];
    NSScanner* scanner = [NSScanner scannerWithString:content];

    MultipleFinder *mf = [[MultipleFinder alloc] init];
      
    while (![scanner isAtEnd]) {
        NSString* line;
        [scanner scanUpToString:@"\n" intoString:&line];
        
        // perform your calculations here
	    [mf assignNums:line];
        
        // output an answer
        printf("%s\n", [[NSString stringWithFormat:@"%d",[mf nextMultiple]] cStringUsingEncoding:NSASCIIStringEncoding]);
    }
    [mf release];
    
    [pool release];
    return 0;
}

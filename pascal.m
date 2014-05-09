// https://www.codeeval.com/open_challenges/18/

/*Objective-C programs are executed via GNUStep on Linux*/

#import <Foundation/Foundation.h>

@interface PascalTriangle : NSObject
{
    int *previousRow;
    int *currentRow;
    int arraySize;
}

-(void) printRow:(int)r;
@end

@implementation PascalTriangle

-(id) init {
    if(self = [super init]) {
        previousRow = currentRow = NULL;
        arraySize = 0;
    }
    return self;
}

-(void) resizeRows:(int)newSize {
    if(arraySize != 0) {
        free(previousRow);
        free(currentRow);
    }
    previousRow = malloc(sizeof(int)*newSize);
    currentRow = malloc(sizeof(int)*newSize);
    arraySize = newSize;
}

-(void) printRow:(int)r {
    // Row r of Pascal's triangle has r elements
    if(arraySize < r) {
        [self resizeRows:r];
    }
    if(r == 1) {
        currentRow[0] = 1;
    } else {
        [self printRow:r-1];
        int *temp = previousRow;
        previousRow = currentRow;
        currentRow = temp;
        currentRow[0] = 1;
        for(int i=1;i<r-1;i++) {
            currentRow[i] = previousRow[i-1] + previousRow[i];
        }
        currentRow[r-1] = 1;
    }

    for(int i=0;i<r;i++) {
        printf("%d ",currentRow[i]);
    }
}

-(void) dealloc {
    free(previousRow);
    free(currentRow);
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

    PascalTriangle *ps = [[PascalTriangle alloc] init];
      
    while (![scanner isAtEnd]) {
        NSString* line;
        [scanner scanUpToString:@"\n" intoString:&line];
        
        // perform your calculations here
	    [ps printRow:line.intValue];
        printf("\n");
    }
    [ps release];
    
    [pool release];
    return 0;
}

// https://www.codeeval.com/open_challenges/6/

/*Objective-C programs are executed via GNUStep on Linux*/

#import <Foundation/Foundation.h>

#define MAX_STRING_SIZE 50

@interface SequenceFinder : NSObject {
    char tempBuffer[MAX_STRING_SIZE+1];
    int tempBufferLength;
    char longestBuffer[MAX_STRING_SIZE+1];
    int longestStringLength;

    char source1[MAX_STRING_SIZE+1];
    int source1Length;
    char source2[MAX_STRING_SIZE+1];
    int source2Length;
}

-(id) initWithArray:(NSArray*)line;
-(int) findSubsequenceWithStart1:(int)start1 start2:(int)start2 bufferPos:(int)p;
-(const char*) longestSubsequence;

@end
@implementation SequenceFinder

-(id) initWithArray:(NSArray*)line {
    if(self = [super init]) {
        NSString *str1 = [line objectAtIndex:0];
        NSString *str2 = [line objectAtIndex:1];
        char buffer1[MAX_STRING_SIZE+1];
        char buffer2[MAX_STRING_SIZE+1];
        // Filter out all characters that aren't in both strings
        strcpy(buffer1,[str1 UTF8String]);
        strcpy(buffer2,[str2 UTF8String]);
        source1Length = 0;
        source2Length = 0;
        for(int i=0;i<str1.length;i++) {
            if(strchr(buffer2,buffer1[i]) != NULL) {
                source1[source1Length] = buffer1[i];
                source1Length++;
            }
        }
        source1[source1Length] = '\0';
        for(int i=0;i<str2.length;i++) {
            if(strchr(buffer1,buffer2[i]) != NULL) {
                source2[source2Length] = buffer2[i];
                source2Length++;
            }
        }
        source2[source2Length] = '\0';

//        printf("Filtered strings to %s / %s\n",source1,source2);

        longestStringLength = 0;
        strcpy(longestBuffer,"");
    }
    return self;
}

-(const char*) longestSubsequence {
    [self findSubsequenceWithStart1:0 start2:0 bufferPos:0];
    return longestBuffer;
}

-(int) findSubsequenceWithStart1:(int)s1 start2:(int)s2 bufferPos:(int)p {
    // Scan until a common character is found
    if(source1Length-s1 < longestStringLength-p ||
       source2Length-s2 < longestStringLength-p) {
        // No chance of finding the longest string from here
        return 0;
    }
    while(s1 < source1Length) {
        for(int k=s2;k<source2Length;k++) {
            if(source1[s1] == source2[k]) {
                tempBuffer[p] = source1[s1];
                // If result is longer than current, update it
                int childLength = [self findSubsequenceWithStart1:s1+1 start2:k+1 bufferPos:p+1];
                if(childLength > longestStringLength) {
                    tempBuffer[p+1] = '\0';
                    //printf("Found new longest string %s\n",tempBuffer);
                    strcpy(longestBuffer,tempBuffer);
                    longestStringLength = childLength;
                }
            }
        }
        // Continue to iterate until no more possibilities are available
        s1++;
    }
    return p+1;
}
@end


int main (int argc, const char * argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    // read filename from the first argument
    NSString* filename = [NSString stringWithCString:argv[1] encoding:NSASCIIStringEncoding];
    NSString* content = [NSString stringWithContentsOfFile:filename encoding:NSASCIIStringEncoding error:nil];
    NSScanner* scanner = [NSScanner scannerWithString:content];

    while (![scanner isAtEnd]) {
        NSString* line;
        [scanner scanUpToString:@"\n" intoString:&line];
        NSArray *strings = [line componentsSeparatedByString:@";"];

        SequenceFinder *sf = [[SequenceFinder alloc] initWithArray:strings];

        
        // output an answer
        const char *answer = [sf longestSubsequence];
        if(answer[0] != '\0') {
            printf("%s\n", answer);
        }
        [sf release];
    }
    
    [pool release];
    return 0;
}

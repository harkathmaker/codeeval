// https://www.codeeval.com/open_challenges/30/
#import <Foundation/Foundation.h>

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
        
        // perform your calculations here
        NSArray *twoSets = [line componentsSeparatedByString:@";"];
        NSMutableSet *set1 = [NSMutableSet setWithArray:[(NSString*)[twoSets objectAtIndex:0] componentsSeparatedByString:@","]];
        NSSet *set2 = [NSSet setWithArray:[(NSString*)[twoSets objectAtIndex:1] componentsSeparatedByString:@","]];
        [set1 intersectSet:set2];
        
        NSArray *intersect = [set1 allObjects];
        NSMutableArray *sortedIntersect = [NSMutableArray arrayWithCapacity:intersect.count];
        for(NSString *s in intersect) {
            [sortedIntersect addObject:[NSNumber numberWithInt:s.intValue]];
        }
        [sortedIntersect sortUsingSelector:@selector(compare:)];
        NSString *answer = [sortedIntersect componentsJoinedByString:@","];

        // output an answer
        printf("%s\n", [answer cStringUsingEncoding:NSASCIIStringEncoding]);
    }
    
    [pool release];
    return 0;
}

// https://www.codeeval.com/open_challenges/102/

#import <Foundation/Foundation.h>

// GNUStep doesn't implement NSJSONSerialization, so do it here
id parseValue(const unichar *data, int idx, int *end);

NSString *parseString(const unichar *data, int idx, int *end) {
    // Skip past the first quote.
    idx++;
    *end = idx;
    while(data[*end] != '"') {
        (*end)++;
    }
    NSString *ret = [NSString stringWithCharacters:data+idx length:*end - idx];
    (*end)++;
    return ret;
}

NSString *parseKey(const unichar *data, int idx, int *end) {
    NSString *ret = parseString(data,idx,end);
    while(data[*end] != ':') {
        (*end)++;
    }
    return ret;
}

NSArray *parseArray(const unichar *data, int idx, int *end) {
    NSMutableArray *ret = [NSMutableArray array];
    idx++;
    do {
        id val = parseValue(data,idx,end);
        [ret addObject:val];
        (*end)++;
        idx = *end;
    } while(data[*end] == ',');
    return ret;
}

NSDictionary *parseDict(const unichar *data, int idx, int *end) {
    NSMutableDictionary *ret = [NSMutableDictionary dictionary];
    *end = idx+1;
    do {
        idx = *end;
        while(data[idx] != '"') {
            idx++;
        }
        NSString *key = parseKey(data,idx,end);
        idx = *end + 1;
        id value = parseValue(data,idx,end);
        [ret setValue:value forKey:key];
    } while(data[*end] == ',');
    return ret;
}

NSNumber *parseNumber(const unichar *data, int idx, int *end) {
    int value = 0;
    while(data[idx] >= '0' && data[idx] <= '9') {
        value *= 10;
        value += data[idx]-'0';
        idx++;
    }
    *end = idx;
    return [NSNumber numberWithInt:value];;
}

id parseValue(const unichar *data, int idx, int *end) {
    while(true) {
        switch(data[idx]) {
            case '"':
                return parseString(data,idx,end);
            case '[':
                return parseArray(data,idx,end);
            case '{':
                return parseDict(data,idx,end);
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return parseNumber(data,idx,end);
            default:
                idx++;
        }
    }
}

id JSONObjectWithString(NSString *data) {
    const unichar *cData = [[data dataUsingEncoding:NSUnicodeStringEncoding] bytes];
    int idx = 0;
    return parseValue(cData, 0, &idx);
}

int getIDSum(id jsonInput) {
    int sum = 0;
    if([jsonInput isKindOfClass:[NSDictionary class]]) {
        NSDictionary *results = jsonInput;
        id label = [results objectForKey:@"label"];
        id idValue = [results objectForKey:@"id"];
        if(label != nil && [idValue isKindOfClass:[NSNumber class]]) {
            sum += ((NSNumber*)idValue).intValue;
        }
        for(id key in results) {
            sum += getIDSum([results objectForKey:key]);
        }
    } else if([jsonInput isKindOfClass:[NSArray class]]){
        NSArray *results = jsonInput;
        for(id child in results) {
            sum += getIDSum(child);
        }
    }
    return sum;
}

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

        id json = JSONObjectWithString(line);
        if(json == nil) {
            printf("Error reading JSON object.\n");
            return -1;
        }

        printf("%d\n",getIDSum(json));
    }
    
    [pool release];
    return 0;
}

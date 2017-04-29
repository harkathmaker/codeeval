import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
	public final long MAX_IP = 4294967296L - 2;
	public final long MIN_IP = 16777216L; // 2^24, or 1 in the 4th byte
	
	private Map<Long,Integer> ipCounts = new HashMap<Long,Integer>();
	
	private Pattern binaryStringPat = Pattern.compile("[01]{24,32}");
	private Pattern binaryDottedPat = Pattern.compile("[01]{1,8}\\.[01]{1,8}\\.[01]{1,8}\\.[01]{1,8}");
	private Pattern decimalStringPat = Pattern.compile("[1-9][0-9]{1,9}");
	private Pattern decimalDottedPat = Pattern.compile("[0-2]?[0-9]{1,2}\\.[0-2]?[0-9]{1,2}\\.[0-2]?[0-9]{1,2}\\.[0-2]?[0-9]{1,2}");
	private Pattern octalStringPat = Pattern.compile("0[0-3][0-7]{10}");
	private Pattern octalDottedPat = Pattern.compile("0[0-3][0-7]{2}\\.0[0-3][0-7]{2}\\.0[0-3][0-7]{2}\\.0[0-3][0-7]{2}");
	private Pattern hexStringPat = Pattern.compile("0x[0-9a-f]{8}");
	private Pattern hexDottedPat = Pattern.compile("0x(0|[0-9a-f]{1,2})\\.0x(0|[0-9a-f]{1,2})\\.0x(0|[0-9a-f]{1,2})\\.0x(0|[0-9a-f]{1,2})");
	
	public void printIPAddress(long n) {
		System.out.printf("%d.%d.%d.%d", n >> 24, (n >> 16) % 256, (n >> 8) % 256, n % 256);
	}
	
	public void incrementIPRecord(long addr) {
		if(ipCounts.containsKey(addr)) {
			ipCounts.put(addr,ipCounts.get(addr)+1);
		} else {
			ipCounts.put(addr, 1);
		}
	}
	
	public long parseDottedAddress(int base, String line, int start, int end) {
		long ret = 0;
		if(base == 16) {
			int k = line.indexOf('x', start)+1;
			for(int i=0;i<4;i++) {
				long innerValue = 0;
				ret <<= 8;
				while(line.charAt(k) >= '0' && line.charAt(k) <= '9') {
					innerValue <<= 4;
					innerValue += line.charAt(k)-'0';
					k++;
				}
				ret += innerValue;
				k = line.indexOf('x', k+1)+1;
			}
		} else {
			int k = line.indexOf('.', start);
			int idx = start;
			for(int i=0;i<4;i++) {
				long innerValue = 0;
				ret <<= 8;
				while(idx < k) {
					innerValue *= base;
					innerValue += line.charAt(idx)-'0';
					idx++;
				}
				ret += innerValue;
				idx = k+1;
				k = line.indexOf('.',k+1);
				if(k == -1) {
					k = end;
				}
			}
		}
		return ret;
	}
	
	public void parseBinaryString(String line) {
		Matcher m = binaryStringPat.matcher(line);
		while(m.find()) {
			Long l = Long.parseLong(line.substring(m.start(), m.end()),2);
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseBinaryDotted(String line) {
		Matcher m = binaryDottedPat.matcher(line);
		while(m.find()) {
			Long l = parseDottedAddress(2,line,m.start(),m.end());
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseDecimalString(String line) {
		Matcher m = decimalStringPat.matcher(line);
		while(m.find()) {
			Long l = Long.parseLong(line.substring(m.start(), m.end()),10);
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseDecimalDotted(String line) {
		Matcher m = decimalDottedPat.matcher(line);
		while(m.find()) {
			Long l = parseDottedAddress(10,line,m.start(),m.end());
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseOctalString(String line) {
		Matcher m = octalStringPat.matcher(line);
		while(m.find()) {
			Long l = Long.parseLong(line.substring(m.start(), m.end()),8);
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseOctalDotted(String line) {
		Matcher m = octalDottedPat.matcher(line);
		while(m.find()) {
			Long l = parseDottedAddress(8,line,m.start(),m.end());
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseHexString(String line) {
		Matcher m = hexStringPat.matcher(line);
		while(m.find()) {
			Long l = Long.parseLong(line.substring(m.start()+2, m.end()),16);
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	public void parseHexDotted(String line) {
		Matcher m = hexDottedPat.matcher(line);
		while(m.find()) {
			Long l = parseDottedAddress(16,line,m.start(),m.end());
			if(l > MAX_IP || l < MIN_IP) {
				continue;
			}
			//System.out.printf("parsed %d from line %s\n", l, line);
			incrementIPRecord(l);
		}
	}
	
	public void processLine(String line) {
		parseBinaryString(line);
		parseBinaryDotted(line);
		parseDecimalString(line);
		parseDecimalDotted(line);
		parseOctalString(line);
		parseOctalDotted(line);
		parseHexString(line);
		parseHexDotted(line);
	}
	
	void printSuspiciousAddresses() {
		List<Long> addrs = new ArrayList<Long>();
		int highestOccurrence = 0;
		for(Map.Entry<Long,Integer> entry : ipCounts.entrySet()) {
			if(entry.getValue() == highestOccurrence) {
				addrs.add(entry.getKey());
			} else if(entry.getValue() > highestOccurrence) {
				highestOccurrence = entry.getValue();
				addrs.clear();
				addrs.add(entry.getKey());
			}
		}
		Collections.sort(addrs);
		for(Long a : addrs) {
			printIPAddress(a);
			System.out.printf(" ");
		}
		System.out.println();
	}

	public static void main(String[] args) throws IOException {
		Main m = new Main();
		
		File file = new File(args[0]);
		BufferedReader in = new BufferedReader(new FileReader(file));
		String line;
		
		while ((line = in.readLine()) != null) {
            if(line.length() > 0) {
                m.processLine(line);
            }
        }
		in.close();
		
		m.printSuspiciousAddresses();
	}

}

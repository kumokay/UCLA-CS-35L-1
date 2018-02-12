#!usr/bin/python

import sys
import argparse


class comm:  
    def __init__(self,file1,file2):
        if file1 == "-":
            f1 = sys.stdin
            f2 = open(file2, 'r')   
        elif file2 == "-":
            f1 = open(file1, 'r')
            f2 = sys.stdin
        else: 
            f1 = open(file1, 'r')
            f2 = open(file2, 'r')
        self.lines1 = f1.readlines()
        self.lines2 = f2.readlines()
        f1.close()
        f2.close()
#       print(self.lines1)
#        print(self.lines2)

#---------Compare function--------------
    def compare(self,unsorted,col1,col2,col3):
        array1 = self.lines1 #a
        array2 = self.lines2 #b
	
        ptr1 = 0 #index pointer to first array 
        ptr2 = 0 #index pointer to second array

        #Check what ever is common and add it to the list.
        #Then go through first file and see if in commonlist
        #Then print second one.
        #-----------() (2,3) ------------
        if unsorted:
            if((not col1 and not col2 and not col3) or (not col1 and col2 and col3) or (not col1 and not col2 and col3)):
                while (ptr1 < len(array1)):
                    flag = False
                    ptr2=0
                    while(ptr2 < len(array2)):
                        if array1[ptr1] == array2[ptr2]: 
                            if col3:
                                sys.stdout.write("")
                                del array2[ptr2]
                                flag = True
                                break;
                            else:
                                sys.stdout.write("\t\t" + array1[ptr1])
                                del array2[ptr2]
                                flag = True
                                break;
                        ptr2+=1
                
                    if (not flag):
                        if col1:
                            sys.stdout.write("")
                        else:
                            sys.stdout.write("" + array1[ptr1])
                    ptr1 += 1
            #Add remaining second array elements
                for temp in array2:
                    if col2:
                        sys.stdout.write("")
                    else:
                        sys.stdout.write("\t" + temp)

                        
            #------(1)-----------
            elif((col1 and not col2 and not col3)):
                while (ptr1 < len(array1)):
                    flag = False
                    ptr2=0
                    while(ptr2 < len(array2)):
                        if array1[ptr1] == array2[ptr2]: 
                            if col3:
                                sys.stdout.write("")
                                del array2[ptr2]
                                flag = True
                                break;
                            else:
                                sys.stdout.write("\t" + array1[ptr1])
                                del array2[ptr2]
                                flag = True
                                break;
                        ptr2+=1
                
                    if (not flag):
                        if col1:
                            sys.stdout.write("")
                        else:
                            sys.stdout.write("" + array1[ptr1])
                    ptr1 += 1
                for temp in array2:
                    if col2:
                        sys.stdout.write("")
                    else:
                        sys.stdout.write("" + temp)
            #-------(2)----------
            elif((not col1 and col2 and not col3)):
                while (ptr1 < len(array1)):
                    flag = False
                    ptr2=0
                    while(ptr2 < len(array2)):
                        if array1[ptr1] == array2[ptr2]:
                            if col3:
                                sys.stdout.write("")
                                del array2[ptr2]
                                flag = True
                                break;
                            else:
                                sys.stdout.write("\t" + array1[ptr1])
                                del array2[ptr2]
                                flag = True
                                break;
                        ptr2+=1

                    if (not flag):
                        if col1:
                            sys.stdout.write("")
                        else:
                            sys.stdout.write("" + array1[ptr1])
                    ptr1 += 1
            #Add remaining second array elements
                for temp in array2:
                    if col2:
                        sys.stdout.write("")
                    else:
                        sys.stdout.write("" + temp)
            #------(1,2)--------------------
            if (col1 and col2 and not col3):
                while (ptr1 < len(array1)):
                    flag = False
                    ptr2=0
                    while(ptr2 < len(array2)):
                        if array1[ptr1] == array2[ptr2]: 
                            if col3:
                                sys.stdout.write("")
                                del array2[ptr2]
                                flag = True
                                break;
                            else:
                                sys.stdout.write("" + array1[ptr1])
                                del array2[ptr2]
                                flag = True
                                break;
                        ptr2+=1
                
                    if (not flag):
                        if col1:
                            sys.stdout.write("")
                        else:
                            sys.stdout.write("")
                    ptr1 += 1
            #Add remaining second array elements
                for temp in array2:
                    if col2:
                        sys.stdout.write("")
                    else:
                        sys.stdout.write("")
            #-----1,3------
            if (col1 and not col2 and col3):
                while (ptr1 < len(array1)):
                    flag = False
                    ptr2=0
                    while(ptr2 < len(array2)):
                        if array1[ptr1] == array2[ptr2]: 
                            if col3:
                                sys.stdout.write("")
                                del array2[ptr2]
                                flag = True
                                break;
                            else:
                                sys.stdout.write("")
                                del array2[ptr2]
                                flag = True
                                break;
                        ptr2+=1
                
                    if (not flag):
                        if col1:
                            sys.stdout.write("")
                        else:
                            sys.stdout.write("")
                    ptr1 += 1
            #Add remaining second array elements
                for temp in array2:
                    if col2:
                        sys.stdout.write("")
                    else:
                        sys.stdout.write("" + temp)






                        
            return
        
        #----------------------------------------------------
        else:  #sorted
                if ((not col1 and col2 and col3) or (not col1 and not col2 and col3) or (not col1 and not col2 and not col3)):
                    #If element 2 is greater 
                    while ptr1 < len(array1) and ptr2 < len(array2):
                        
                        if array1[ptr1] < array2[ptr2]:
                            if col1:
                                sys.stdout.write("")
                            else:
                                sys.stdout.write("" + array1[ptr1])
                            ptr1+=1
                            continue;
                        #If element 1 is greater
                        if array1[ptr1] > array2[ptr2]:
                            if col2:
                                sys.stdout.write("")
                            else:
                                sys.stdout.write("\t" + array2[ptr2])
                            ptr2+=1
                            
                            continue;
                        #If the elements are equal. 
                        if array1[ptr1] == array2[ptr2]:
                            if col3:
                                sys.stdout.write("")
                            else:
                                sys.stdout.write("\t\t" + array1[ptr1])
                            ptr1+=1
                            ptr2+=1
                            continue;
                    
                #Print remainders
                    while ptr2 < len(array2):
                        if col2:
                            sys.stdout.write("")
                        else:
                            sys.stdout.write("\t" + array2[ptr2])
                        ptr2+=1
                    while ptr1 < len(array1):
                        if col1:
                            sys.stdout.write("")            
                        else:
                            sys.stdout.write("" + array1[ptr1])
                        ptr1+=1
                    
                #----(1)----
                elif(col1 and  not col2 and not col3):
                    while ptr1 < len(array1) and ptr2 < len(array2):
                        if array1[ptr1] < array2[ptr2]:
                            sys.stdout.write("")
                            ptr1+=1
                            continue;
                        if array1[ptr1] > array2[ptr2]:
                            sys.stdout.write("" + array2[ptr2])
                            ptr2+=1
                            continue;
                        if array1[ptr1] == array2[ptr2]:
                            sys.stdout.write("\t" + array1[ptr1])
                            ptr1+=1
                            ptr2+=1
                            continue;    
                    while ptr2 < len(array2):
                        sys.stdout.write("" + array2[ptr2])
                        ptr2+=1
                #-----(2)--------
                elif(not col1 and col2 and not col3):
                    while ptr1 < len(array1) and ptr2 < len(array2):
                        if array1[ptr1] < array2[ptr2]:
                            sys.stdout.write("" + array1[ptr1])
                            ptr1+=1
                            continue;
                        if array1[ptr1] > array2[ptr2]:
                            sys.stdout.write("")
                            ptr2+=1
                            continue;
                        if array1[ptr1] == array2[ptr2]:
                            sys.stdout.write("\t" + array1[ptr1])
                            ptr1+=1
                            ptr2+=1
                            continue;    
                    while ptr1 < len(array1):
                        sys.stdout.write("" + array1[ptr1])
                        ptr1+=1
                #---(1,2)------
                elif(col1 and col2 and not col3):
                    while ptr1 < len(array1) and ptr2 < len(array2):
                        if array1[ptr1] < array2[ptr2]:
                            sys.stdout.write("")
                            ptr1+=1
                            continue;
                        if array1[ptr1] > array2[ptr2]:
                            sys.stdout.write("")
                            ptr2+=1
                            continue;
                        if array1[ptr1] == array2[ptr2]:
                            sys.stdout.write("" + array1[ptr1])
                            ptr1+=1
                            ptr2+=1
                            continue;
                #-----(1,3)-------
                elif(col1 and not col2 and col3):
                    while ptr1 < len(array1) and ptr2 < len(array2):
                        if array1[ptr1] < array2[ptr2]:
                            sys.stdout.write("")
                            ptr1+=1
                            continue;
                        if array1[ptr1] > array2[ptr2]:
                            sys.stdout.write("" + array2[ptr2])
                            ptr2+=1
                            continue;
                        if array1[ptr1] == array2[ptr2]:
                            sys.stdout.write("")
                            ptr1+=1
                            ptr2+=1
                            continue;
                    while ptr2 < len(array2):
                        sys.stdout.write("" + array2[ptr2])
                        ptr2+=1
                
                    
                


def main():
    usage_msg = """prog [-123] [-u] file1 file2

-1 Suppress the output column of lines unique to file1.

-2 Suppress the output column of lines unique to file2.

-3 Suppress the output column of lines duplicated in file1 and file2.

FILE1 and FILE2 are sorted unless the -u flag is used
"""

    parser = argparse.ArgumentParser(usage=usage_msg)
    
    parser.add_argument("-1", action="store_true", dest="col1", default=False,
                      help="Suppress column 1 (lines unique to FILE1)")
    parser.add_argument("-2", action="store_true", dest="col2", default=False,
                      help="Suppress column 2 (lines unique to FILE2)")
    parser.add_argument("-3", action="store_true", dest="col3", default=False,
                      help="Suppress column 3")
    parser.add_argument("-u", action="store_true", dest="unsorted", default=False,
                      help="Compare unsorted files")

    options, args = parser.parse_known_args()

    try: 
        col1 = bool(options.col1)
    except:
        parser.error("invalid argument for -1: {0}".
                     format(options.col1))
    try:
        col2 = bool(options.col2)
    except:
        parser.error("invalid argument for -2: {0}".
                     format(options.col2))
    try:
        col3 = bool(options.col3)
    except:
        parser.error("invalid argument for -3: {0}".
                     format(options.col3))
    try:
        unsorted = bool(options.unsorted)
    except:
        parser.error("invalid argument for -u: {0}".
                     format(options.unsorted))

    if len(args) != 2:
        parser.error("You need two files")
	
    file1 = args[0]
    file2 = args[1]

    if file1 == "-" and file2 == "-":
        parser.error("Two files in std input")

    try:
        reader = comm(file1,file2)
        reader.compare(unsorted,col1,col2,col3)
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()

    




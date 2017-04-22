#!/usr/bin/python                                                                                                                                            
import sys, string, locale
from optparse import OptionParser


def main():
    locale.setlocale(locale.LC_ALL, 'C')
    version_msg = "%prog 2.0"                                                                                                                                                      
    usage_msg = "%prog [-123u] FILE1 FILE2"

    parser = OptionParser(version=version_msg, usage=usage_msg)  

    parser.add_option("-1", action="store_true", dest="one", default=0, help="supress line 1")
    parser.add_option("-2", action="store_true", dest="two", default=0, help="supress line 2")
    parser.add_option("-3", action="store_true", dest="three", default=0, help="supress line 3")
    parser.add_option("-u", action="store_true", dest="U", default=0, help="use it if unsorted")

    options, args = parser.parse_args(sys.argv[1:])
    
    if len(args)!=2:
        parser.error("The number of argument is wrong!")
    
    file1=args[0]
    file2=args[1]
    lines1 = []
    lines2 =[]
    
    if file2=="-":
        lines1=sys.stdin.readlines()

        try:
            f2 = open (file1, 'r')
            lines2 = f2.readlines()
            f2.close()
        except:
            parser.error("Cannot load file")

    else:
        try:
            f1 = open (file1, 'r')
            f2 = open (file2, 'r')
            lines1 = f1.readlines()
            lines2 = f2.readlines()
            f1.close()
            f2.close()
        except:
            parser.error("Cannot load file")
        
        
    U=options.U
    one=options.one
    two=options.two
    three=options.three


    columnumn1 = []
    column2 = []
    column3 = []

    if U==0:

        if lines1 != sorted(lines1) or lines2 != sorted(lines2):
            print ("They are not sorted")

        column1=lines1
        column2=lines2
        for i in lines1:
            if i in lines2:
                column3.append(i)

        for i in column3:
            if i in column2:
                column2.remove(i)
        for i in column3:
            if i in column1:
                column1.remove(i)

        ans=sorted(column1+column2+column3)


        for i in ans:
            if i in column1 and one!=1:
                sys.stdout.write(i)
            if i in column2 and one!=1 and two!=1:
                sys.stdout.write("\t"+i)
            elif i in column2 and one==1 and two!=1:
                sys.stdout.write(i)
            if i in column3 and one!=1 and two!=1 and three!=1:
                sys.stdout.write("\t\t"+i)
            elif i in column3 and one==1 and two!=1 and three!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and one!=1 and two==1 and three!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and one==1 and two==1 and hree!=1:
                sys.stdout.write(i)

    if U==1:
        for i in lines1:
            if i in lines2:
                column3.append(i)

        for i in column3:
            if i in lines2:
                lines2.remove(i)
            
        for i in lines1:
            if i in column3 and one!=1 and two!=1 and three!=1:
                sys.stdout.write("\t\t"+i)
            elif i in column3 and one==1 and two!=1 and three!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and one!=1 and two==1 and three!=1:
                sys.stdout.write("\t"+i)
            elif i in column3 and one==1 and two==1 and three!=1:
                sys.stdout.write(i)
            elif i not in column3 and one!=1:
                sys.stdout.write(i)
        for i in lines2:
            if one!=1 and two!=1:
                sys.stdout.write("\t"+i)
            elif one==1 and two!=1:
                sys.stdout.write(i)
                                                                                                                                                                                                                                                                                                                    
if __name__ == "__main__":
    main()

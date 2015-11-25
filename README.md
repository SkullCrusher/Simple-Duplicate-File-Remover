# Simple-Duplicate-File-Remover


	Written by David Harkins.
	Usage:
	  -D Delete the duplicates.
	  -L <fullpath.extension> Dump all the duplicates to a list.
	  -S Show extra information about the search.

  Example (1): -D -L <Path> -S <Path to folder to check>
      - Deletes the duplicate files, dumps their filenames to a file and shows extra information.
      
  Example (2): -D <Path to folder to check>
      - Deletes the duplicates.
      
  Example (3): -L <Path> <Path to folder to check?
      - Saves the duplicates to a file of the location Path.


  Please note:
  
    This only runs on 64 bit machines.
      To patch this to run on 32 bit you will have to replace the variable type of long long with 
      something of your choosing. Also the AVL tree will have to be changed to handle the new variable.
      
    The operating system this was made for was Windows.
      I tested this on Windows 8 but this should work on Windows 7 and forward but I have not tried.
      
    

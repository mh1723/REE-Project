# REE-Project
<h1>Reverse Engineering Project Notes</h1>
<h2>10/09/2016</h2>
<ol>
<li>Started new visual studio project, added Main_Students.cpp, SHA-256.cpp, SHA-256.h, and Test_Main_Students.cpp</li>
<li>Ran EDTool_D.exe from command line, successfully decrypted "encrypted.tx".</li>
<li>Opened EDTool_D.exe with WinDbg and Ida Pro.</li>
<li>Ran program in WinDbg without arguments, got error output "Error – Could not open input file ..."</li>
<li>Searched for error string in Ida Pro, found at 498D80.  Referenced by sub_434EB0.  Followed link.</li>
<li>Renamed sub_432CE9 to printf</li>
<li>Renamed sub_434EB0 to openInputFile as refered to in Main_Student.cpp</li>
</ol>

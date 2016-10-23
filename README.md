# REE-Project
<h1>Reverse Engineering Project Notes</h1>

<h2>10/09/2016</h2>
<ol>
	<li>Started new visual studio project, added Main_Students.cpp, SHA-256.cpp, SHA-256.h, and Test_Main_Students.cpp</li>
	<li>Ran EDTool_D.exe from command line, successfully decrypted "encrypted.tx".</li>
	<li>Opened EDTool_D.exe with WinDbg and Ida Pro.</li>
	<li>Ran program in WinDbg without arguments, got error output "Error – Could not open input file ..."</li>
	<li>Searched for error string in Ida Pro, found at 498D80.  Referenced by sub_434EB0.  Followed link.</li>
	<li>Renamed sub_434EB0 to openInputFile as refered to in Main_Student.cpp</li>
	<li>Renamed sub_434A20 to decryptText as refered to in Main_Student.cpp</li>li>
</ol>

<h2> 10/23/2016</h2>
<ol>
	<li> Previous Notes were for the wrong project file.  Thankfully locations for the two functions were the same. Repeating work from above on new PE file.</li>
	<li> Pretty sure sub_434F40 is  Main_Student.  Renamed. </li>
	<li> Stepping through  Main_Student, found locfation of default file name at 00498db8.  Very interesting stuff right after:
		<ol>
			<li>cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0</li>
			<li>248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1</li>
			<li>ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad</li>
			<li>abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq</li>
		</ol>
	</li>
	<li> Pretty sure function sub_43CDA0 at 00434ED7 is to fopen. Renamed. </li>
	<li> Pretty sure function sub_43E230 at 00434EF1 is printf.  Renamed</li>
	<li> function sub_0043DD20 at 00434A9B is probably a call to memset. Renamed </li>
	<li> Not sure what the call at 00434AB3 is doing, but I think it has something to do with the password.  The pointer it sends in starts with all 0's from the call to memset above.  On return, the value is %$2TTSkjshdfo9087@.</li>
	<li>the call at 00434AC2 sends the above ptr as param.  The return is 13. The program then comares this value to 1 and 256.  If below 1, print error, password is to long.</li>
	<li> Stopped at loc_434B03: </li>

</ol>

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
	<li> Not sure what the call at 00434AB3 is doing, but I think it may be fread or mmap or something similiar.  On return, the value is %$2TTSkjshdfo9087@, which is the start of the encrypted.txt file.</li>
	<li> The call at 00434AC2 sends the above ptr as param.  The return is 0x13 which is 19 (the length of the ptr). This is probably strlen.  The program then compares this value to 1 and 256.  If below 1 or above 256, print error.</li>
	<li> Stopped at loc_434B03: </li>
</ol>
<h2> 11/01/2016</h2>
<ol>
<li> After reading through the call at 00434AC2, pretty sure that is strlen.  Renamed </li>
<li> ebp+154 holds the byte length of the password.</li>
<li> loc_434B03 has to do with hashing - need to look at this</li>
<li> Renamed call at 00434B73 to malloc</li>
<li> ebp+160 contains the number of bytes to allocate and ebp+114 is the pointer to the allocated space </li>
<li> arg0 is the pointer to the encrypted.txt file</li>
<li> started going thru the call at 00434AB3.  It does refer to fgets - but it also does some comparisions.  I think it's looking for
the password in the file by looking if it starts with %$2 and ends with 7.  I'm tired.  Going to sleep.</li>
</ol>
<h2> 11/03/2016</h2>
<ol>
<li>looking at call to sub_433153 at break point 00434B37.  Signature is siminiar to ret = func(0, fp, len_pass-1, buf), where fp is the pointer to the encrypted.txt file, len_pass-1 is the length of the password -1, and buf is a pointer to a local variable that hasn't been used yet.  </li>
<li>Immediatly after pushing ebp and moving esp into ebp, apon entering the function calls sub_432483 with a value stored in eax (not pushed to stack).  It does some address arithmetic in a loop using the value in eax as a counter of sorts.  Not sure what's happening.  No return value.  esp has chaned, difference between ebp and esp is the value pushed into eax.  This call is some funky way of making room on the stack for local variables.</li>
<li> Nest, it checks if the first arg was 0.  If so, it calls memset(buf, 0, 64).  If not, it looks like it opens the file in rb mode and reads arg_0 bytes.  Either way arg_0 get stored in local variable vaar_C. </li>
<li> Next (at 0043BFFF) it calls sub_432A55 with a pointer to a local variable as a parameter.  This is where I stop for now.  Been at the office for 10 hours, think my butt may be rooted to this chair. Need to go home.</li>
</ol>
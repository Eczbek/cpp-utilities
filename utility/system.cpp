
#include "./system.hpp"

// from https://sourceforge.net/p/predef/wiki/OperatingSystems/
std::string_view utility::system::name () {
#ifdef _AIX || __TOS_AIX__
	return "AIX";
#elif __ANDROID__
	return "Android";
#elif UTS
	return "Amdahl UTS";
#elif AMIGA || __amigaos__
	return "AmigaOS";
#elif aegis
	return "Apollo AEGIS";
#elif apollo
	return "Apollo Domain/OS";
#elif __BEOS__
	return "BeOS";
#elif __bg__ || __THW_BLUEGENE__
	return "Blue Gene";
#elif _SYSTYPE_BSD
	return "BSD";
#elif __bsdi__ 
	return "BSD/OS";
#elif __convex__
	return "ConvexOS";
#elif __CYGWIN__
	return "Cygwin";
#elif DGUX || __DGUX__ || __dgux__
	return "DG/UX";
#elif __DragonFly__
	return "DragonFly";
#elif _SEQUENT_ || sequent
	return "DYNIX/ptx";
#elif __ECOS
	return "eCos";
#elif __EMX__
	return "EMX";
#elif __FreeBSD_kernel__ && __GLIBC__
	return "GNU/kFreeBSD";
#elif __FreeBSD__ || __FreeBSD_kernel__
	return "FreeBSD";
#elif __GNU__ || __gnu_hurd__
	return "GNU/Hurd";
#elif __gnu_linux__
	return "GNU/Linux";
#elif __hiuxmpp
	return "HI-UX MPP";
#elif hpux || _hpux || __hpux
	return "HP-UX";
#elif __OS400__
	return "IBM OS/400";
#elif __INTEGRITY
	return "INTEGRITY";
#elif __INTERIX
	return "Interix";
#elif sgi || __sgi
	return "IRIX";
#elif linux || __linux || __linux__
	return "Linux";
#elif __Lynx__
	return "LynxOS";
#elif macintosh || Macintosh || __APPLE__ && __MACH__
	return "MacOS";
#elif __OS9000__ || _OSK
	return "Microware OS-9";
#elif __minix
	return "Minix";
#elif __MORPHOS__
	return "MorphOS";
#elif mpeix || __mpexl
	return "MPE/iX";
#elif MSDOS || _MSDOS || __MSDOS__ || __DOS__
	return "MSDOS";
#elif __NetBSD__
	return "NetBSD";
#elif __TANDEM
	return "NonStop";
#elif __nucleus__
	return "Nucleus RTOS";
#elif __OpenBSD__
	return "OpenBSD";
#elif OS2 || _OS2 || __OS2__ || __TOS_OS2__
	return "OS/2";
#elif __palmos__
	return "Palm OS";
#elif EPLAN9
	return "Plan 9";
#elif pyr
	return "Pyramid DC/OSx";
#elif __QNX__ || __QNXNTO__
	return "QNX";
#elif sinux
	return "Reliant UNIX";
#elif M_I386 || M_XENIX || _SCO_DS
	return "SCO OpenServer";
#elif sun || __sun
	return "Solaris";
#elif __VOS__
	return "Stratus VOS";
#elif __sysv__ || __SVR4 || __srv4__ || _SYSTYPE_SVR4
	return "SVR4";
#elif __SYLLABLE__
	return "Syllable";
#elif __SYMBIAN32__
	return "Symbian OS";
#elif __osf || __osf__
	return "Tru64";
#elif ultrix || __ultrix || __ultrix__ || unix && vax
	return "Ultrix";
#elif _UNICOS
	return "UNICOS";
#elif _CRAY || __crayx1
	return "UNICOS/mp";
#elif __unix || __unix__
	return "UNIX";
#elif sco || _UNIXWARE7
	return "UnixWare";
#elif _UWIN
	return "U/WIN";
#elif VMS || __VMS
	return "VMS";
#elif __vxworks || __VXWORKS__
	return "VxWorks";
#elif _WIN16 || _WIN32 || _WIN64 || __WIN32__ || __TOS_WIN__ || __WINDOWS__
	return "Windows";
#elif _WIN32_WCE
	return "Windows CE";
#elif _WINDU_SOURCE
	return "Wind/U";
#elif __MVS__ || __HOS_MVS__ || __TOS_MVS__
	return "z/OS";
#endif
	return "other";
}

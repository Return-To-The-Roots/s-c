#!/bin/bash

# Editable Variables
CMAKE_COMMAND=cmake

###############################################################################

if [ -z "$(type -p $CMAKE_COMMAND)" ] ; then
	echo "You have to install CMake"
	exit 1
fi

mecho()
{
	COLOR=$1
	shift
	$CMAKE_COMMAND -E cmake_echo_color --bold $COLOR "$*"
}

###############################################################################

if [ ! -e bin ] ; then
	mecho --blue "Creating symlink «bin» ..."
	ln -s . bin
fi

if [ ! -e RTTR ] ; then
	if [ -e ../RTTR ] ; then
		mecho --blue "Creating symlink «RTTR» ..."
		ln -s ../RTTR RTTR
	else
		mecho --red "Directory «RTTR» missing!"
		exit 1
	fi
fi

if [ ! -e share ] ; then
	mecho --blue "Creating symlink «share» ..."
	ln -s . share
fi

if [ ! -e s25rttr ] ; then
	mecho --blue "Creating symlink «s25rttr» ..."
	ln -s . s25rttr
fi

if [ ! -e S2 ] ; then
	if [ -e ../S2 ] ; then
		mecho --blue "Creating symlink «S2» ..."
	ln -s ../S2 S2
	else
		mecho --red "Directory «S2» missing!"
		exit 1
	fi
fi

if [ -z "$ARCH" ] ; then
	if [ "$(uname -s)" = "Darwin" ] ; then
		ARCH=apple.local
	else
		ARCH=linux.local
	fi
fi

if ( [ ! -f cleanup.sh ] && [ -f ../build/cleanup.sh ] ) ; then
	ln -s ../build/cleanup.sh cleanup.sh
fi

if ( [ ! -f cmake.sh ] && [ -f ../build/cmake.sh ] ) ; then
	ln -s ../build/cmake.sh cmake.sh
fi

###############################################################################

PREFIX=/usr/local
BINDIR=
DATADIR=
as_cr_letters='abcdefghijklmnopqrstuvwxyz'
as_cr_LETTERS='ABCDEFGHIJKLMNOPQRSTUVWXYZ'
as_cr_Letters=$as_cr_letters$as_cr_LETTERS
as_cr_digits='0123456789'
as_cr_alnum=$as_cr_Letters$as_cr_digits

while test $# != 0 ; do
	case $1 in
	--*=*)
		ac_option=`expr "X$1" : 'X\([^=]*\)='`
		ac_optarg=`expr "X$1" : 'X[^=]*=\(.*\)'`
		ac_shift=:
	;;
	*)
		ac_option=$1
		ac_optarg=yes
		ac_shift=shift
	;;
	esac

	case $ac_option in
	-prefix | --prefix)
		$ac_shift
		PREFIX=$ac_optarg
	;;
        -iprefix | --iprefix)
		$ac_shift
		IPREFIX=$ac_optarg
	;;
	-bindir | --bindir)
		$ac_shift
		BINDIR=$ac_optarg
	;;
	-datadir | --datadir)
		$ac_shift
		DATADIR=$ac_optarg
	;;
	-arch | --arch | -target | --target)
		$ac_shift
		ARCH=$ac_optarg
	;;
  	-enable-* | --enable-*)
    	ac_feature=`expr "x$ac_option" : 'x-*enable-\([^=]*\)'`
    	# Reject names that are not valid shell variable names.
    	expr "x$ac_feature" : ".*[^-._$as_cr_alnum]" >/dev/null &&
      	{
      		echo "error: invalid feature name: $ac_feature" >&2
   			{ (exit 1); exit 1; };
   		}
    	ac_feature=`echo $ac_feature | sed 's/[-.]/_/g'`
    	if [ -z "$ac_optarg" ] ; then
    		ac_optarg="yes"
    		echo foo
    	fi
    	eval enable_$ac_feature=\$ac_optarg
    ;;
    *)
		echo "Unknown option: $ac_option"
		exit 1
	;;
	esac

	shift
done

if [ -z "$IPREFIX" ] ; then
	IPREFIX=$PREFIX
fi

if [ -z "$BINDIR" ] ; then
	BINDIR=$IPREFIX/bin
fi

if [ -z "$DATADIR" ] ; then
	DATADIR=$IPREFIX/share/s25rttr
fi

###############################################################################

PARAMS=""

echo "Setting Path-Prefix to \"$PREFIX\""
PARAMS="$PARAMS -DPREFIX=$PREFIX"

echo "Setting Install-Prefix to \"$IPREFIX\""
PARAMS="$PARAMS -DCMAKE_INSTALL_PREFIX=$IPREFIX"

echo "Setting Architecture to \"$ARCH\""
PARAMS="$PARAMS -DCOMPILEFOR_PLATFORM=$ARCH"

echo "Setting Binary Dir to \"$BINDIR\""
PARAMS="$PARAMS -DBINDIR=$BINDIR"

echo "Setting Data Dir to \"$DATADIR\""
PARAMS="$PARAMS -DDATADIR=$DATADIR"

case "$enable_debug" in
yes|YES|Yes)
	mecho --magenta "Activating debug build"
	PARAMS="$PARAMS -DCMAKE_BUILD_TYPE=Debug"
;;
*)
	case "$enable_reldeb" in
	yes|YES|Yes)
		mecho --magenta "Activating release build with debug information"
		PARAMS="$PARAMS -DCMAKE_BUILD_TYPE=RelWithDebInfo"
	;;
	*)
		mecho --magenta "Activating release build"
		PARAMS="$PARAMS -DCMAKE_BUILD_TYPE=Release"
	;;
	esac
;;
esac

###############################################################################

mecho --blue "Running \"cmake $PARAMS\""
$CMAKE_COMMAND $PARAMS ..

if [ $? != 0 ] ; then
	mecho --red "An error occured - please check above!"
	exit 1
fi

mecho --blue "Now type \"make\" to build project"

exit 0

###############################################################################

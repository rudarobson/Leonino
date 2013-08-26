#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/delay/delay.c src/usb/ep0.c src/usb/ep1.c src/usb/ep2.c src/usb/usb.c src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/delay/delay.p1 ${OBJECTDIR}/src/usb/ep0.p1 ${OBJECTDIR}/src/usb/ep1.p1 ${OBJECTDIR}/src/usb/ep2.p1 ${OBJECTDIR}/src/usb/usb.p1 ${OBJECTDIR}/src/main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/delay/delay.p1.d ${OBJECTDIR}/src/usb/ep0.p1.d ${OBJECTDIR}/src/usb/ep1.p1.d ${OBJECTDIR}/src/usb/ep2.p1.d ${OBJECTDIR}/src/usb/usb.p1.d ${OBJECTDIR}/src/main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/delay/delay.p1 ${OBJECTDIR}/src/usb/ep0.p1 ${OBJECTDIR}/src/usb/ep1.p1 ${OBJECTDIR}/src/usb/ep2.p1 ${OBJECTDIR}/src/usb/usb.p1 ${OBJECTDIR}/src/main.p1

# Source Files
SOURCEFILES=src/delay/delay.c src/usb/ep0.c src/usb/ep1.c src/usb/ep2.c src/usb/usb.c src/main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/delay/delay.p1: src/delay/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/delay 
	${MP_CC} --pass1 src/delay/delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\delay" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/delay/delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\delay" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/delay/delay.p1: > ${OBJECTDIR}/src/delay/delay.p1.d
	@cat ${OBJECTDIR}/src/delay/delay.dep >> ${OBJECTDIR}/src/delay/delay.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/delay/delay.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/ep0.p1: src/usb/ep0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/ep0.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/ep0.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/ep0.p1: > ${OBJECTDIR}/src/usb/ep0.p1.d
	@cat ${OBJECTDIR}/src/usb/ep0.dep >> ${OBJECTDIR}/src/usb/ep0.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/ep0.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/ep1.p1: src/usb/ep1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/ep1.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/ep1.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/ep1.p1: > ${OBJECTDIR}/src/usb/ep1.p1.d
	@cat ${OBJECTDIR}/src/usb/ep1.dep >> ${OBJECTDIR}/src/usb/ep1.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/ep1.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/ep2.p1: src/usb/ep2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/ep2.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/ep2.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/ep2.p1: > ${OBJECTDIR}/src/usb/ep2.p1.d
	@cat ${OBJECTDIR}/src/usb/ep2.dep >> ${OBJECTDIR}/src/usb/ep2.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/ep2.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/usb.p1: src/usb/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/usb.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/usb.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/usb.p1: > ${OBJECTDIR}/src/usb/usb.p1.d
	@cat ${OBJECTDIR}/src/usb/usb.dep >> ${OBJECTDIR}/src/usb/usb.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	${MP_CC} --pass1 src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/main.p1: > ${OBJECTDIR}/src/main.p1.d
	@cat ${OBJECTDIR}/src/main.dep >> ${OBJECTDIR}/src/main.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/main.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/delay/delay.p1: src/delay/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/delay 
	${MP_CC} --pass1 src/delay/delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\delay" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/delay/delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\delay" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/delay/delay.p1: > ${OBJECTDIR}/src/delay/delay.p1.d
	@cat ${OBJECTDIR}/src/delay/delay.dep >> ${OBJECTDIR}/src/delay/delay.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/delay/delay.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/ep0.p1: src/usb/ep0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/ep0.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/ep0.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/ep0.p1: > ${OBJECTDIR}/src/usb/ep0.p1.d
	@cat ${OBJECTDIR}/src/usb/ep0.dep >> ${OBJECTDIR}/src/usb/ep0.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/ep0.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/ep1.p1: src/usb/ep1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/ep1.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/ep1.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/ep1.p1: > ${OBJECTDIR}/src/usb/ep1.p1.d
	@cat ${OBJECTDIR}/src/usb/ep1.dep >> ${OBJECTDIR}/src/usb/ep1.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/ep1.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/ep2.p1: src/usb/ep2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/ep2.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/ep2.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/ep2.p1: > ${OBJECTDIR}/src/usb/ep2.p1.d
	@cat ${OBJECTDIR}/src/usb/ep2.dep >> ${OBJECTDIR}/src/usb/ep2.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/ep2.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb/usb.p1: src/usb/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	${MP_CC} --pass1 src/usb/usb.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/usb/usb.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src\usb" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/usb/usb.p1: > ${OBJECTDIR}/src/usb/usb.p1.d
	@cat ${OBJECTDIR}/src/usb/usb.dep >> ${OBJECTDIR}/src/usb/usb.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	${MP_CC} --pass1 src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@${MP_CC} --scandep  src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\src" -P -N255 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24   -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s"  
	@echo ${OBJECTDIR}/src/main.p1: > ${OBJECTDIR}/src/main.p1.d
	@cat ${OBJECTDIR}/src/main.dep >> ${OBJECTDIR}/src/main.p1.d
	@${FIXDEPS} "${OBJECTDIR}/src/main.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) -odist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  -mdist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.map --summary=default,-psect,-class,+mem,-hex --chip=$(MP_PROCESSOR_OPTION) -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=icd3 -P -N255 --warn=0 --cp=16 -Blarge --double=24    --output=default,-inhx032 -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s" ${OBJECTFILES_QUOTED_IF_SPACED}    
	${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.hex
else
dist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) -odist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -mdist/${CND_CONF}/${IMAGE_TYPE}/Libraries.X.${IMAGE_TYPE}.map --summary=default,-psect,-class,+mem,-hex --chip=$(MP_PROCESSOR_OPTION) -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,+config,+clib,+plib --opt=default,+asm,-asmfile,+speed,-space,9 -P -N255 --warn=0 --cp=16 -Blarge --double=24    --output=default,-inhx032 -g --asmlist "--errformat=%%f:%%l: error: %%s" "--msgformat=%%f:%%l: advisory: %%s" "--warnformat=%%f:%%l warning: %%s" ${OBJECTFILES_QUOTED_IF_SPACED}    
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

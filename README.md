# Generic-Stack-On-C

tests_[n].[c|h] files, possibly, may help you understand how to use GenericStack.h header.  
also check started comment in GenericStack.h file for understand some restriction.  

GenericStackSetEmptyConfig.h - help to reset all Config params(just include it)  
GenericStackConfigEnum.h - help to see bit flags for GS_CONFIG macro

macros:  
- GENERIC_STACK_TYPE : set stack type  
- GENERIC_STACK_POSTFIX : set struct postfix, need when you use twice struct with the same type  
(or when you use GS.h header in different files q.v. {NOTE:3})       
- GENERIC_STACK_LOG_FILE : set name of log file  :|  
- WITHOUT_AUTO_CHECK_VALID : remove all validation functions  
- CANARY_FOR_[STRUCT | DATA] : turn on canary  
- HASH_[STRUCT | DATA] : turn on hash  
- CAPACITY_IS_POW2 : aligns capacity by 2^n  
- NOT_REAL_EMPTY_STACK : it must be uint, set stack capacity when you use new_empty_generic_stack(type)     
- ELEM_DUMPABLE : allow to log stack elems, but for use it you should realise appropriate function  
- COMPARABLE : allow to compare two stack, but for it you should realise appropriate function  
- CANARY_FS_USE_PTR : use struct ptr in struct canaries  
- GS_WITH_ERROR_VALIDATE : allow not fall by assert, but use error param for error tracking  

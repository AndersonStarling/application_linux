cmd_/home/ntai/Linux_Embedded/application_project/hello_module/Module.symvers := sed 's/\.ko$$/\.o/' /home/ntai/Linux_Embedded/application_project/hello_module/modules.order | scripts/mod/modpost -m -a  -o /home/ntai/Linux_Embedded/application_project/hello_module/Module.symvers -e -i Module.symvers   -T -
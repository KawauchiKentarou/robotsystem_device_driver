cmd_/home/ubuntu/kadai1/Module.symvers := sed 's/ko$$/o/' /home/ubuntu/kadai1/modules.order | scripts/mod/modpost -m -a   -o /home/ubuntu/kadai1/Module.symvers -e -i Module.symvers   -T -

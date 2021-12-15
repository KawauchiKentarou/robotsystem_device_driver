cmd_/home/ubuntu/kadai1/modules.order := {   echo /home/ubuntu/kadai1/kadai1.ko; :; } | awk '!x[$$0]++' - > /home/ubuntu/kadai1/modules.order

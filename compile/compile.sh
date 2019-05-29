#Program

#change make file and app name
make_file=compile/build.mk
app=bin/utf_8

#add parameters
param1=
param2=
param3=
param4=
param5=

#------------------------------------------------------#

#process definition
function process_app {
	clear #clear screen
	echo building................ #message
	make --file=$make_file #build app
	#don't run of failed
	if [ $? -eq 0 ]; then
		echo running................ #message
		$app $param1 $param2 $param3 $param4 $param5 #run app
	fi
}

#process is called
process_app

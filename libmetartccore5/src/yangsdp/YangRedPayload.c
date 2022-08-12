//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangsdp/YangRedPayload.h>
#include <yangutil/sys/YangCString.h>
void yang_create_redPayloaddes(YangRedPayload* red,uint8_t pt, char* encode_name, int32_t sample,int32_t channel){
	red->sample=sample;
	red->pt=pt;
	strncpy(red->name,encode_name, sizeof(red->name) - 1);
	red->channel=channel;
}

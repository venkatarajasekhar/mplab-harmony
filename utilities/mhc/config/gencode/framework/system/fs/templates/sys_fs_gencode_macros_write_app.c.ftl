
<#macro macro_sys_fs_write_app_c_includes>
</#macro>

<#macro macro_sys_fs_write_app_c_global_data>

static char ${APP_NAME?lower_case}FsWritePath[] = "${("CONFIG_SYS_FS_MEDIA_MOUNT_1_NAME_IDX" + ("CONFIG_APP_SYS_FS_WRITE_MEDIA" + "${HCONFIG_APP_INSTANCE}")?eval)?eval}/${("CONFIG_APP_SYS_FS_WRITE_FILENAME" + "${HCONFIG_APP_INSTANCE}")?eval}";
static uint8_t __attribute__ ((aligned (16))) ${APP_NAME?lower_case}FsWriteData[] = "${("CONFIG_APP_SYS_FS_DATA" + "${HCONFIG_APP_INSTANCE}")?eval}";
</#macro>


<#macro macro_sys_fs_write_app_c_callback_functions>
</#macro>

<#macro macro_sys_fs_write_app_c_local_functions>
/* state machine for the File System */
static void ${APP_NAME?upper_case}_FS_WRITE_Task(void)
{
    static SYS_FS_ERROR FsError;
    static uint8_t HandleAttempts;
    static uint32_t TotalBytesWritten;
    static SYS_FS_HANDLE FileHandle;

    switch (${APP_NAME?lower_case}Data.fsWriteStateMachine)
    {
        default:
        case ${APP_NAME?upper_case}_FS_WRITE_STATE_START:
            HandleAttempts = 0;
            ${APP_NAME?lower_case}Data.fsWriteStateMachine =  ${APP_NAME?upper_case}_FS_WRITE_STATE_OPEN;
            break;

        case ${APP_NAME?upper_case}_FS_WRITE_STATE_OPEN:
            /* open the file to write - create file if it does not exist */
            FileHandle = SYS_FS_FileOpen(${APP_NAME?lower_case}FsWritePath, SYS_FS_FILE_OPEN_WRITE_PLUS);
            if (FileHandle == SYS_FS_HANDLE_INVALID)
            {
                /* try 10 times to get the handle - allow auto-mount to finish */
                if (++HandleAttempts > 10)
                {
                    FsError = SYS_FS_Error();
                    ${APP_NAME?lower_case}Data.fsWriteStateMachine =  ${APP_NAME?upper_case}_FS_WRITE_STATE_ERROR;
                }
            }
            else
            {
                TotalBytesWritten = 0;
                ${APP_NAME?lower_case}Data.fsWriteStateMachine =  ${APP_NAME?upper_case}_FS_WRITE_STATE_FILEOPS;
            }
            break;

        case ${APP_NAME?upper_case}_FS_WRITE_STATE_FILEOPS:
            {
                size_t BytesWritten = SYS_FS_FileWrite(FileHandle, (const void *)${APP_NAME?lower_case}FsWriteData,
                    sizeof(${APP_NAME?lower_case}FsWriteData) - TotalBytesWritten);
                if (BytesWritten == (size_t)-1)
                {
                    /* error */
                    FsError = SYS_FS_Error();
                    ${APP_NAME?lower_case}Data.fsWriteStateMachine =  ${APP_NAME?upper_case}_FS_WRITE_STATE_ERROR;
                    return;
                }
                else
                {
                    TotalBytesWritten += BytesWritten;
                    /* have we written all the bytes now? */
                    if (TotalBytesWritten >= sizeof(${APP_NAME?lower_case}FsWriteData))
                    {
                        SYS_FS_FileClose(FileHandle);
                        ${APP_NAME?lower_case}Data.fsWriteStateMachine =  ${APP_NAME?upper_case}_FS_WRITE_STATE_DONE;
                    }
                }
            }
            break;

        case ${APP_NAME?upper_case}_FS_WRITE_STATE_DONE:
            break;

        /* if we get to this state - something went wrong - check FsError for status */
        case ${APP_NAME?upper_case}_FS_WRITE_STATE_ERROR:
            break;
    }
}

</#macro>

<#macro macro_sys_fs_write_app_c_initialize>

    /* Place the File System state machine in its initial state */
    ${APP_NAME?lower_case}Data.fsWriteStateMachine = ${APP_NAME?upper_case}_FS_WRITE_STATE_START;
</#macro>

<#macro macro_sys_fs_write_app_c_tasks_data>
</#macro>

<#macro macro_sys_fs_write_app_c_tasks_state_init>
</#macro>

<#macro macro_sys_fs_write_app_c_tasks_calls_after_init>
</#macro>

<#macro macro_sys_fs_write_app_c_tasks_state_service_tasks>

            /* run the state machine for servicing the file system */
            ${APP_NAME?upper_case}_FS_WRITE_Task();
</#macro>

<#macro macro_sys_fs_write_app_c_tasks_states>
</#macro>

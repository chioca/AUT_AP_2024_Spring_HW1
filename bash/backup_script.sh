#!/bin/bash

# 显示错误信息并退出
function error_exit {
    echo "错误: $1"
    exit 1
}

# 检查必需的参数
if [ -z "$1" ] || [ -z "$2" ]; then
    error_exit "源路径和目标路径是必需的。"
fi

# 将参数分配给变量
SOURCE_PATH=$1
DESTINATION_PATH=$2
COMPRESSION_LEVEL=1

# 检查压缩级别参数
while [[ "$#" -gt 0 ]]; do
    case $3 in
        -c|--compression) COMPRESSION_LEVEL="$4"; shift ;;
        *) ;;
    esac
    shift
done

# 验证源路径
if [ ! -d "$SOURCE_PATH" ]; then
    error_exit "源路径 '$SOURCE_PATH' 不存在或不是目录。"
fi

# 验证目标路径
if [ ! -d "$DESTINATION_PATH" ]; then
    error_exit "目标路径 '$DESTINATION_PATH' 不存在或不是目录。"
fi

# 获取当前日期和时间
CURRENT_DATE=$(date +%Y-%m-%d)
START_TIME=$(date +%H:%M:%S\ %Z)
MACHINE_INFO=$(uname -a)

# 获取要备份的目录名称
DIRECTORY_NAME=$(basename "$SOURCE_PATH")

# 格式化备份文件名
BACKUP_FILE="$DESTINATION_PATH/${CURRENT_DATE}_${DIRECTORY_NAME}.zip"
LOG_FILE="$DESTINATION_PATH/backup_log.txt"

# 开始备份
START_TIME_EPOCH=$(date +%s)
zip -r -"$COMPRESSION_LEVEL" "$BACKUP_FILE" "$SOURCE_PATH" || error_exit "创建备份失败。"
END_TIME_EPOCH=$(date +%s)
END_TIME=$(date +%H:%M:%S\ %Z)

# 计算备份持续时间
DURATION=$((END_TIME_EPOCH - START_TIME_EPOCH))
DURATION_MINUTES=$((DURATION / 60))
DURATION_SECONDS=$((DURATION % 60))

# 获取备份的文件和目录数量
FILES_BACKED_UP=$(zipinfo -t "$BACKUP_FILE" | grep -oP '\d+(?= files)')
DIRECTORIES_BACKED_UP=$(zipinfo -t "$BACKUP_FILE" | grep -oP '\d+(?= directories)')

# 写入日志文件
{
    echo "Backup Log Report"
    echo
    echo "Date: $CURRENT_DATE"
    echo "Time: $START_TIME"
    echo "Machine Information:"
    echo
    echo "Operating System: $MACHINE_INFO"
    echo
    echo "Backup Details:"
    echo
    echo "Source Path: $SOURCE_PATH"
    echo "Destination Path: $BACKUP_FILE"
    echo "Compression Level: $COMPRESSION_LEVEL"
    echo "Files Backed Up: $FILES_BACKED_UP"
    echo "Directories Backed Up: $DIRECTORIES_BACKED_UP"
    echo
    echo "Backup Summary:"
    echo
    echo "Start Time: $START_TIME"
    echo "End Time: $END_TIME"
    echo "Total Duration: ${DURATION_MINUTES} minutes ${DURATION_SECONDS} seconds"
    echo
} > "$LOG_FILE"

# 打印成功信息
echo "Backup of $DESTINATION_PATH completed successfully."
echo "Saved to $BACKUP_FILE"

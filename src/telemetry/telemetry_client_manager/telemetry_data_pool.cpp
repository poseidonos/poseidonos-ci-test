/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "src/telemetry/telemetry_client_manager/telemetry_data_pool.h"

namespace pos
{
TelemetryDataPool::TelemetryDataPool(void)
{
}
TelemetryDataPool::~TelemetryDataPool(void)
{
}

void
TelemetryDataPool::SetLog(std::string id, uint32_t value)
{
    std::string curTime = _GetCurTime();
   TelemetryLogEntry entry(curTime, value);
   pool[id] = entry;
///////////////////// for test, will be removed
   TelemetryLogEntry tempRet;
   int ret = GetLog(id, tempRet);
   if (ret == -1)
   {
        POS_TRACE_ERROR(EID(TELEMETRY_), "[Telemetry Log] ERROR!!! Failed to GetLog, id:{}", id);
   }
   else
   {
       POS_TRACE_ERROR(EID(TELEMETRY_), "[Telemetry Log] id:{}, time:{}, value:{}", id, tempRet.GetTime(), tempRet.GetValue());
   }
//////////////////////
}

int
TelemetryDataPool::GetLog(std::string id, TelemetryLogEntry& outLog)
{
    auto entry = pool.find(id);
    if (entry == pool.end())
    {
        POS_TRACE_ERROR(EID(TELEMETRY_), "[Telemetry] error!! can not find telemetry Item:{}", id);
        return -1;
    }
    else
    {
        outLog = (*entry).second;
        return 0;
    }
}

const std::string
TelemetryDataPool::_GetCurTime(void)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int
TelemetryDataPool::GetNumLogEntries(void)
{
    return pool.size();
}

} // namespace pos
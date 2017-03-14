/*
   Copyright (C) 2017 Red Hat, Inc.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

       * Redistributions of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in
         the documentation and/or other materials provided with the
         distribution.
       * Neither the name of the copyright holder nor the names of its
         contributors may be used to endorse or promote products derived
         from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * This header contains definition for the device that
 * allows to send streamed data to the server.
 */

#ifndef SPICE_STREAM_DEVICE_H_
#define SPICE_STREAM_DEVICE_H_

#include <spice/types.h>

/*
 * The structure are all "naturally aligned"
 * containing integers up to 64 bit.
 * All numbers are in little endian format.
 */

#define STREAM_DEVICE_PROTOCOL 1

typedef struct StreamDevHeader {
    /* should be STREAM_DEVICE_PROTOCOL */
    uint8_t protocol_version;
    uint8_t padding;
    /* as defined in StreamDevType enumeration */
    uint16_t type;
    /* size of the following message */
    uint32_t size;
} StreamDevHeader;

typedef enum StreamDevType {
    /* invalid, do not use */
    STREAM_TYPE_INVALID = 0,
    /* allows to send version information */
    STREAM_TYPE_CAPABILITIES,
    /* send screen resolution */
    STREAM_TYPE_FORMAT,
    /* stream data */
    STREAM_TYPE_DATA,
    /* server ask to start a new stream */
    STREAM_TYPE_START_STOP,
    /* server notify errors to guest */
    STREAM_TYPE_NOTIFY_ERROR,
} StreamDevType;

/* generic extension capabilities */
typedef struct StreamMsgCapabilities {
    uint32_t num_capabilities;
    uint32_t capabilities[0];
} StreamMsgCapabilities;

/* Define the format of the stream, start a new stream.
 * This message is sent by the guest to the host to
 * tell the host the new stream format.
 */
typedef struct StreamMsgFormat {
    /* screen resolution/stream size */
    uint32_t width;
    uint32_t height;
    /* as defined in SpiceVideoCodecType enumeration */
    uint8_t codec;
    uint8_t padding1[3];
} StreamMsgFormat;

/* This message contains just raw data stream.
 * This message is sent by the guest to the host.
 */
typedef struct StreamMsgData {
    uint8_t data[0];
} StreamMsgData;

/* Tell to stop current stream and possibly start a new one.
 * This message is sent by the host to the guest.
 * Allows to communicate the codecs supported by the clients.
 * The agent should stop the old stream and if any codec in the
 * list is supported start streaming (as Mjpeg is always supported
 * agent should stop only on a real stop request).
 */
typedef struct StreamMsgStartStop {
    /* supported codecs, 0 to stop streaming */
    uint8_t num_codecs;
    /* as defined in SpiceVideoCodecType enumeration */
    uint8_t codecs[0];
} StreamMsgStartStop;

/* Tell guest about invalid protocol.
 * This message is sent by the host to the guest.
 * The server will stop processing data from the guest.
 */
typedef struct StreamMsgNotifyError {
    /* numeric error code.
     * Currently not defined, set to 0.
     */
    uint32_t error_code;
    /* String message, UTF-8 encoded.
     * This field terminate with the message.
     * Not necessary NUL-terminated.
     */
    uint8_t msg[0];
} StreamMsgNotifyError;

#endif /* SPICE_STREAM_DEVICE_H_ */

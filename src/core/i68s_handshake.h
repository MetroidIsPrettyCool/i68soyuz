#ifndef I68S_HANDSHAKE_H
#define I68S_HANDSHAKE_H

enum HandshakeResult {
    HANDSHAKE_SUCCESS,
    HANDSHAKE_VERSION_MISMATCH,
    // HANDSHAKE_TIMEOUT,
    HANDSHAKE_WRITE_ERROR,
    HANDSHAKE_READ_ERROR
};

struct I68Config {
    enum HandshakeResult handshake_result;
    unsigned char apollo_version[3];
};

// perform handshake with i68apollo
//
// returns struct i68config
//
// only the handshake_result field is guaranteed to be initialized. The states of the other fields will depend on the
// value of handshake_result.
//
// if handshake_result is HANDSHAKE_SUCCESS, all fields will be initialized
//
// if handshake_result is HANDSHAKE_VERSION_MISMATCH, only apollo_version will be initialized
//
// if handshake_result is any other value, no other fields will be initialized
struct I68Config* handshake(void);

#endif

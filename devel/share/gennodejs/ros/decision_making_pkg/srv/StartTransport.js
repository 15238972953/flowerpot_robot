// Auto-generated. Do not edit!

// (in-package decision_making_pkg.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class StartTransportRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.placement_type = null;
      this.placement_spacing = null;
      this.start = null;
    }
    else {
      if (initObj.hasOwnProperty('placement_type')) {
        this.placement_type = initObj.placement_type
      }
      else {
        this.placement_type = 0;
      }
      if (initObj.hasOwnProperty('placement_spacing')) {
        this.placement_spacing = initObj.placement_spacing
      }
      else {
        this.placement_spacing = 0.0;
      }
      if (initObj.hasOwnProperty('start')) {
        this.start = initObj.start
      }
      else {
        this.start = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type StartTransportRequest
    // Serialize message field [placement_type]
    bufferOffset = _serializer.int8(obj.placement_type, buffer, bufferOffset);
    // Serialize message field [placement_spacing]
    bufferOffset = _serializer.float32(obj.placement_spacing, buffer, bufferOffset);
    // Serialize message field [start]
    bufferOffset = _serializer.bool(obj.start, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type StartTransportRequest
    let len;
    let data = new StartTransportRequest(null);
    // Deserialize message field [placement_type]
    data.placement_type = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [placement_spacing]
    data.placement_spacing = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [start]
    data.start = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a service object
    return 'decision_making_pkg/StartTransportRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c75117dab7ae6528b49f68a745dce8d4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 请求部分
    int8 placement_type      # 0=网格摆放, 1=三角错位摆放
    float32 placement_spacing # 摆放间距（米）
    bool start               # 开始标志
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new StartTransportRequest(null);
    if (msg.placement_type !== undefined) {
      resolved.placement_type = msg.placement_type;
    }
    else {
      resolved.placement_type = 0
    }

    if (msg.placement_spacing !== undefined) {
      resolved.placement_spacing = msg.placement_spacing;
    }
    else {
      resolved.placement_spacing = 0.0
    }

    if (msg.start !== undefined) {
      resolved.start = msg.start;
    }
    else {
      resolved.start = false
    }

    return resolved;
    }
};

class StartTransportResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
      this.message = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
      if (initObj.hasOwnProperty('message')) {
        this.message = initObj.message
      }
      else {
        this.message = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type StartTransportResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    // Serialize message field [message]
    bufferOffset = _serializer.string(obj.message, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type StartTransportResponse
    let len;
    let data = new StartTransportResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [message]
    data.message = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.message);
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'decision_making_pkg/StartTransportResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '937c9679a518e3a18d831e57125ea522';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 响应部分
    bool success
    string message
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new StartTransportResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    if (msg.message !== undefined) {
      resolved.message = msg.message;
    }
    else {
      resolved.message = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: StartTransportRequest,
  Response: StartTransportResponse,
  md5sum() { return 'a29e616be9ef3884c858e9b72ec65988'; },
  datatype() { return 'decision_making_pkg/StartTransport'; }
};

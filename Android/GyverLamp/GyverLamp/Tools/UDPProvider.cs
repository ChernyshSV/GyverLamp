using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Android.Content;
using Android.Support.V7.Preferences;

namespace GyverLamp.Tools
{
    class UDPProvider
    {
        private Context _context;

        public UDPProvider(Context context)
        {
            _context = context;
        }

        internal OperationResult<string> Call(string message)
        {
            try
            {
                var udpSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp)
                {
                    ReceiveTimeout = 2000
                };

                var endPoint = new IPEndPoint(IPAddress.Parse(GetIPAddress()), GetPort());

                var send_buffer = Encoding.ASCII.GetBytes(message);
                udpSocket.SendTo(send_buffer, endPoint);

                var breceived_byte = new byte[1024];
                var byterec = udpSocket.Receive(breceived_byte);

                return new OperationResult<string>(Encoding.UTF8.GetString(breceived_byte, 0, byterec));
            }
            catch (Exception ex)
            {
                return new OperationResult<string>(ex);
            }
        }

        private int GetPort()
        {
            var sharedPref = PreferenceManager.GetDefaultSharedPreferences(_context);
            return int.Parse(sharedPref.GetString("end_point_port", ""));
        }

        private string GetIPAddress()
        {
            var sharedPref = PreferenceManager.GetDefaultSharedPreferences(_context);
            return sharedPref.GetString("end_point_address", "");
        }
    }

    class OperationResult<T>
    {
        public T Result { get; }
        public bool IsFaulted { get; }
        public Exception Exception { get; }
        public OperationResult(T result)
        {
            Result = result;
        }

        public OperationResult(Exception exception)
        {
            IsFaulted = true;
            Exception = exception;
        }
    }
}
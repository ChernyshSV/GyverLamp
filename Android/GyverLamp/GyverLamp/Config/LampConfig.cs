namespace GyverLamp.Config
{
    class LampConfig
    {
        public int PowerMode { get; set; }
        public int Brightness { get; set; }
        public int Speed { get; set; }
        public int Scale { get; set; }
        public int EffectNumber { get; set; }
    }

    static class LampCommands
    {
        public const string PowerOn = "P_ON";
        public const string PowerOff = "P_OFF";
        public const string GetSettings = "GET";
        public const string SetBrightness = "BRI";
        public const string SetSpeed = "SPD";
        public const string SetScale = "SCA";
        public const string SetEffect = "EFF";
        public const string SetAlarm = "ALM_SET";

        public const string GetAlarms = "ALM_GET";
    }
}
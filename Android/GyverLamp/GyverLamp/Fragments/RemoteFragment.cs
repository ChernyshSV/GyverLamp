using System;
using System.Threading.Tasks;
using Android.OS;
using Android.Support.V4.App;
using Android.Views;
using Android.Widget;
using GyverLamp.Config;
using GyverLamp.Tools;

using Xamarin.Essentials;

namespace GyverLamp.Fragments
{
    public class RemoteFragment : Fragment
    {
        private ImageButton _btnPower;
        private SeekBar _seekBrightness;
        private TextView _brightnessSubtitle;
        private SeekBar _seekSpeed;
        private UDPProvider _udpProvider;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            _udpProvider = new UDPProvider(Context);
            var cur = System.Threading.Thread.CurrentThread;

            Task.Run(() =>
            {
                var configs = _udpProvider.Call(LampCommands.GetSettings);
                MainThread.BeginInvokeOnMainThread(() =>
                {
                    ParceResult(configs);
                });
            });
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var view = inflater.Inflate(Resource.Layout.remote_panel, container, false);

            _btnPower = view.FindViewById<ImageButton>(Resource.Id.btn_power);
            _seekBrightness = view.FindViewById<SeekBar>(Resource.Id.seekBar_brightness);
            _brightnessSubtitle = view.FindViewById<TextView>(Resource.Id.brightness_subtitle);
            _seekSpeed = view.FindViewById<SeekBar>(Resource.Id.seekBar_speed);

            _btnPower.Click += OnPowerClick;

            _seekBrightness.ProgressChanged += OnBrightnessValueChanged;
            _seekSpeed.ProgressChanged += OnSpeedChanged;

            var spinner = view.FindViewById<Spinner>(Resource.Id.effects_spinner);
            spinner.ItemSelected += Spinner_ItemSelected;

            return view;
        }

        private async void Spinner_ItemSelected(object sender, AdapterView.ItemSelectedEventArgs e)
        {
            ParceResult(await Task.Run(() => _udpProvider.Call(LampCommands.SetEffect + e.Position)));
        }

        private async void NumPick_ValueChanged(object sender, NumberPicker.ValueChangeEventArgs e)
        {
            ParceResult(await Task.Run(() => _udpProvider.Call(LampCommands.SetEffect + e.NewVal)));
        }

        private async void OnSpeedChanged(object sender, SeekBar.ProgressChangedEventArgs e)
        {
            ParceResult(await Task.Run(() => _udpProvider.Call(LampCommands.SetSpeed + e.Progress)));
        }

        private async void OnBrightnessValueChanged(object sender, SeekBar.ProgressChangedEventArgs e)
        {
            ParceResult(await Task.Run(() => _udpProvider.Call(LampCommands.SetBrightness + e.Progress)));
        }

        internal LampConfig LampConfig { get; private set; }

        private async void OnPowerClick(object sender, EventArgs e)
        {
            if (LampConfig == null)
            {
                var result = await Task.Run(() => { return _udpProvider.Call(LampCommands.GetSettings); }).ConfigureAwait(true);

                ParceResult(result);


                if (result.IsFaulted)
                {
                    return;
                }
            }

            var command = LampConfig.PowerMode == 1 ? LampCommands.PowerOff : LampCommands.PowerOn;

            ParceResult(await Task.Run(() => { return _udpProvider.Call(command); }));
        }

        private void ParceResult(OperationResult<string> res)
        {
            if (res.IsFaulted)
            {
                var text = res.Exception.Message;

                var toast = Toast.MakeText(Context, text, ToastLength.Short);
                toast.SetGravity(GravityFlags.Center, 0, 0);
                toast.Show();

                return;
            }

            //CURR 2 15 30 40 1

            var str = res.Result.Split(' ');
            var lampConfig = new LampConfig
            {
                EffectNumber = int.Parse(str[1]),
                Brightness = int.Parse(str[2]),
                Speed = int.Parse(str[3]),
                Scale = int.Parse(str[4]),
                PowerMode = int.Parse(str[5])
            };

            LampConfig = lampConfig;
        }
    }
}
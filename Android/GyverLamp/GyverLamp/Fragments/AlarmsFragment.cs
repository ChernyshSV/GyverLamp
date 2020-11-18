using System;
using System.Collections.Generic;
using Android.OS;
using Android.Support.Design.Widget;
using Android.Support.V4.App;
using Android.Views;
using Android.Widget;

namespace GyverLamp.Fragments
{
    public class AlarmsFragment : Fragment
    {
        private FloatingActionButton _btnCreateAlarm;
        private ListView _list;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var view = inflater.Inflate(Resource.Layout.alarms_panel, container, false);

            _btnCreateAlarm = view.FindViewById<FloatingActionButton>(Resource.Id.btn_create);
            _list = view.FindViewById<ListView>(Resource.Id.alarms_list);

            _btnCreateAlarm.Click += OnCreateNewAlarm;

            return view;
        }

        private void OnCreateNewAlarm(object sender, EventArgs e)
        {
            var currentDateTime = DateTime.Now;
            new Android.App.TimePickerDialog(Context, SetTime, currentDateTime.Hour, currentDateTime.Minute, true)
                .Show();
        }


        private void SetTime(object sender, Android.App.TimePickerDialog.TimeSetEventArgs e)
        {
            
        }
    }
}
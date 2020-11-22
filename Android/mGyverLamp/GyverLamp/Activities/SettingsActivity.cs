
using Android.App;
using Android.OS;
using Android.Support.V7.App;
using GyverLamp.Fragments;

namespace GyverLamp.Activities
{
    [Activity(Label = "Settings")]
    public class SettingsActivity : AppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            Xamarin.Essentials.Platform.Init(this, savedInstanceState);
            SetContentView(Resource.Layout.activity_settings);

            SupportFragmentManager.BeginTransaction().Replace(Resource.Id.fragment_container, new SettingsFragment()).Commit();
        }
    }
}
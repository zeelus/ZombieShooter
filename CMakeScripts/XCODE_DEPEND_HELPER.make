# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ZombieShooter.Release:
/Users/gilbertgwizdala/Desktop/ZombieShooter/bin/ZombieShooter:\
	/usr/local/opt/urho3d/lib/Urho3D/libUrho3D.a
	/bin/rm -f /Users/gilbertgwizdala/Desktop/ZombieShooter/bin/ZombieShooter


PostBuild.ZombieShooter.RelWithDebInfo:
/Users/gilbertgwizdala/Desktop/ZombieShooter/bin/ZombieShooter:\
	/usr/local/opt/urho3d/lib/Urho3D/libUrho3D.a
	/bin/rm -f /Users/gilbertgwizdala/Desktop/ZombieShooter/bin/ZombieShooter


PostBuild.ZombieShooter.Debug:
/Users/gilbertgwizdala/Desktop/ZombieShooter/bin/ZombieShooter:\
	/usr/local/opt/urho3d/lib/Urho3D/libUrho3D.a
	/bin/rm -f /Users/gilbertgwizdala/Desktop/ZombieShooter/bin/ZombieShooter




# For each target create a dummy ruleso the target does not have to exist
/usr/local/opt/urho3d/lib/Urho3D/libUrho3D.a:

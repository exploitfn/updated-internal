#pragma once 
namespace id
{
	Vector3 bottom, bottom_2, head, head_2, neck, chest, pelvis, rshoulder, relbow, rhand, rthigh, rknee, rfoot, rfootout, lshoulder, lelbow, lhand, lthigh, lknee, lfoot, lfootout;
	Vector2 s_bottom, s_bottom_2, s_head, s_head_2, s_neck, s_chest, s_pelvis, s_rshoulder, s_relbow, s_rhand, s_rthigh, s_rknee, s_rfoot, s_rfootout, s_lshoulder, s_lelbow, s_lhand, s_lthigh, s_lknee, s_lfoot, s_lfootout;

	bool Get_id(APlayerController* controller, AFortPawn* player)
	{
		bool success = true;
		//MessageBoxA(0, "GetBoneLocation", "GetBoneLocation", MB_OK);
		bottom = player->GetBoneLocation(0);
		//MessageBoxA(0, "w2s", "w2s", MB_OK);
		if (success && !controller->w2s(bottom, &s_bottom)) success = false;
		bottom_2 = bottom; bottom_2.z -= 8;
		if (success && !controller->w2s(bottom_2, &s_bottom_2)) success = false;
		head = player->GetBoneLocation(68);
		if (success && !controller->w2s(head, &s_head)) success = false;
		head_2 = head; head_2.z += 20;
		if (success && !controller->w2s(head_2, &s_head_2)) success = false;
		neck = player->GetBoneLocation(67);
		if (success && !controller->w2s(neck, &s_neck)) success = false;
		chest = player->GetBoneLocation(7); chest.z += 7;
		if (success && !controller->w2s(chest, &s_chest)) success = false;
		pelvis = player->GetBoneLocation(2);
		if (success && !controller->w2s(pelvis, &s_pelvis)) success = false;
		rshoulder = player->GetBoneLocation(38);
		if (success && !controller->w2s(rshoulder, &s_rshoulder)) success = false;
		relbow = player->GetBoneLocation(39);
		if (success && !controller->w2s(relbow, &s_relbow)) success = false;
		rhand = player->GetBoneLocation(40);
		if (success && !controller->w2s(rhand, &s_rhand)) success = false;
		rthigh = player->GetBoneLocation(78);
		if (success && !controller->w2s(rthigh, &s_rthigh)) success = false;
		rknee = player->GetBoneLocation(79);
		if (success && !controller->w2s(rknee, &s_rknee)) success = false;
		rfoot = player->GetBoneLocation(82);
		if (success && !controller->w2s(rfoot, &s_rfoot)) success = false;
		rfootout = player->GetBoneLocation(83);
		if (success && !controller->w2s(rfootout, &s_rfootout)) success = false;
		lshoulder = player->GetBoneLocation(9);
		if (success && !controller->w2s(lshoulder, &s_lshoulder)) success = false;
		lelbow = player->GetBoneLocation(10);
		if (success && !controller->w2s(lelbow, &s_lelbow)) success = false;
		lhand = player->GetBoneLocation(11);
		if (success && !controller->w2s(lhand, &s_lhand)) success = false;
		lthigh = player->GetBoneLocation(71);
		if (success && !controller->w2s(lthigh, &s_lthigh)) success = false;
		lknee = player->GetBoneLocation(72);
		if (success && !controller->w2s(lknee, &s_lknee)) success = false;
		lfoot = player->GetBoneLocation(75);
		if (success && !controller->w2s(lfoot, &s_lfoot)) success = false;
		lfootout = player->GetBoneLocation(76);
		if (success && !controller->w2s(lfootout, &s_lfootout)) success = false;
		return success;
	}
}
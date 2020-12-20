/*
 --------------------------------------------------------------------------
 ServicePTZ.cpp
 
 Implementation of functions (methods) for the service:
 ONVIF ptz.wsdl server side
-----------------------------------------------------------------------------
*/


#include "soapPTZBindingService.h"
#include "ServiceContext.h"
#include "smacros.h"
#include "wsseapi.h"


int PTZBindingService::GetServiceCapabilities(_tptz__GetServiceCapabilities *tptz__GetServiceCapabilities, _tptz__GetServiceCapabilitiesResponse &tptz__GetServiceCapabilitiesResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    return SOAP_OK;
}

int PTZBindingService::GetConfigurations(_tptz__GetConfigurations *tptz__GetConfigurations, _tptz__GetConfigurationsResponse &tptz__GetConfigurationsResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int GetPTZPreset(struct soap *soap, tt__PTZPreset* ptzp, int number)
{
    ptzp->token = soap_new_std__string(soap);
    *ptzp->token = std::to_string(number);
    ptzp->Name = soap_new_std__string(soap);
    *ptzp->Name  = std::to_string(number);
    ptzp->PTZPosition = soap_new_tt__PTZVector(soap);;
    ptzp->PTZPosition->PanTilt          = soap_new_tt__Vector2D(soap);
    ptzp->PTZPosition->PanTilt->x       = 0.0;
    ptzp->PTZPosition->PanTilt->y       = 0.0;
    ptzp->PTZPosition->Zoom             = soap_new_tt__Vector1D(soap);
    ptzp->PTZPosition->Zoom->x          = 1;

    return SOAP_OK;
}

int PTZBindingService::GetPresets(_tptz__GetPresets *tptz__GetPresets, _tptz__GetPresetsResponse &tptz__GetPresetsResponse)
{
    int i;

    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    soap_default_std__vectorTemplateOfPointerTott__PTZPreset(soap, &tptz__GetPresetsResponse._tptz__GetPresetsResponse::Preset);
    for (i = 0; i < 8; i++) {
        tt__PTZPreset* ptzp;
        ptzp = soap_new_tt__PTZPreset(soap);
        tptz__GetPresetsResponse.Preset.push_back(ptzp);
        GetPTZPreset(this->soap, ptzp, i);
    }

    return SOAP_OK;
}

int PTZBindingService::SetPreset(_tptz__SetPreset *tptz__SetPreset, _tptz__SetPresetResponse &tptz__SetPresetResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::RemovePreset(_tptz__RemovePreset *tptz__RemovePreset, _tptz__RemovePresetResponse &tptz__RemovePresetResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GotoPreset(_tptz__GotoPreset *tptz__GotoPreset, _tptz__GotoPresetResponse &tptz__GotoPresetResponse)
{
    char cmd[1024];

    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    ServiceContext* ctx = (ServiceContext*)this->soap->user;

    const char *username = soap_wsse_get_Username(this->soap);
    if (!username)
        return this->soap->error;
    if (ctx->user != username)
        return SOAP_FAULT;
    if (soap_wsse_verify_Password(this->soap, ctx->password.c_str()))
        return this->soap->error;

    if (tptz__GotoPreset == NULL) {
        return SOAP_OK;
    }
    if (tptz__GotoPreset->ProfileToken.c_str() == NULL) {
        return SOAP_OK;
    }
    if (tptz__GotoPreset->PresetToken.c_str() == NULL) {
        return SOAP_OK;
    }

    if ((tptz__GotoPreset->PresetToken.back() >= '0') && (tptz__GotoPreset->PresetToken.back() <= '9')) {
        sprintf(cmd, "%s %c", ctx->get_ptz_node()->get_move_preset().c_str(), tptz__GotoPreset->PresetToken.back());
        system(cmd);
    }

    return SOAP_OK;
}

int PTZBindingService::GetStatus(_tptz__GetStatus *tptz__GetStatus, _tptz__GetStatusResponse &tptz__GetStatusResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GetConfiguration(_tptz__GetConfiguration *tptz__GetConfiguration, _tptz__GetConfigurationResponse &tptz__GetConfigurationResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int GetPTZNode(struct soap *soap, tt__PTZNode* ptzn)
{
    ptzn->token = "PTZNodeToken";
    ptzn->Name = soap_new_std__string(soap);
    *ptzn->Name  = "PTZ";

    ptzn->SupportedPTZSpaces = soap_new_tt__PTZSpaces(soap);;
    soap_default_std__vectorTemplateOfPointerTott__Space2DDescription(soap, &ptzn->SupportedPTZSpaces->tt__PTZSpaces::RelativePanTiltTranslationSpace);
    soap_default_std__vectorTemplateOfPointerTott__Space1DDescription(soap, &ptzn->SupportedPTZSpaces->tt__PTZSpaces::RelativeZoomTranslationSpace);
    soap_default_std__vectorTemplateOfPointerTott__Space2DDescription(soap, &ptzn->SupportedPTZSpaces->tt__PTZSpaces::ContinuousPanTiltVelocitySpace);
    soap_default_std__vectorTemplateOfPointerTott__Space1DDescription(soap, &ptzn->SupportedPTZSpaces->tt__PTZSpaces::ContinuousZoomVelocitySpace);
    soap_default_std__vectorTemplateOfPointerTott__Space1DDescription(soap, &ptzn->SupportedPTZSpaces->tt__PTZSpaces::PanTiltSpeedSpace);
    soap_default_std__vectorTemplateOfPointerTott__Space1DDescription(soap, &ptzn->SupportedPTZSpaces->tt__PTZSpaces::ZoomSpeedSpace);

    tt__Space2DDescription* ptzs1;
    ptzs1 = soap_new_tt__Space2DDescription(soap);
    ptzn->SupportedPTZSpaces->RelativePanTiltTranslationSpace.push_back(ptzs1);

    tt__Space1DDescription* ptzs2;
    ptzs2 = soap_new_tt__Space1DDescription(soap);
    ptzn->SupportedPTZSpaces->RelativeZoomTranslationSpace.push_back(ptzs2);

    tt__Space2DDescription* ptzs3;
    ptzs3 = soap_new_tt__Space2DDescription(soap);
    ptzn->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace.push_back(ptzs3);

    tt__Space1DDescription* ptzs4;
    ptzs4 = soap_new_tt__Space1DDescription(soap);
    ptzn->SupportedPTZSpaces->ContinuousZoomVelocitySpace.push_back(ptzs4);

    tt__Space1DDescription* ptzs5;
    ptzs5 = soap_new_tt__Space1DDescription(soap);
    ptzn->SupportedPTZSpaces->PanTiltSpeedSpace.push_back(ptzs5);

    tt__Space1DDescription* ptzs6;
    ptzs6 = soap_new_tt__Space1DDescription(soap);
    ptzn->SupportedPTZSpaces->ZoomSpeedSpace.push_back(ptzs6);

    ptzs1->URI         = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace";
    ptzs1->XRange      = soap_new_tt__FloatRange(soap);
    ptzs1->XRange->Min = -1.0;
    ptzs1->XRange->Max = 1.0;
    ptzs1->YRange      = soap_new_tt__FloatRange(soap);
    ptzs1->YRange->Min = -1.0;
    ptzs1->YRange->Max = 1.0;

    ptzs2->URI            = "http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace";
    ptzs2->XRange         = soap_new_tt__FloatRange(soap);
    ptzs2->XRange->Min    = -1.0;
    ptzs2->XRange->Max    = 1.0;

    ptzs3->URI         = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace";
    ptzs3->XRange      = soap_new_tt__FloatRange(soap);
    ptzs3->XRange->Min = -1.0;
    ptzs3->XRange->Max = 1.0;
    ptzs3->YRange      = soap_new_tt__FloatRange(soap);
    ptzs3->YRange->Min = -1.0;
    ptzs3->YRange->Max = 1.0;

    ptzs4->URI            = "http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace";
    ptzs4->XRange         = soap_new_tt__FloatRange(soap);
    ptzs4->XRange->Min    = -1.0;
    ptzs4->XRange->Max    = 1.0;

    ptzs5->URI            = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace";
    ptzs5->XRange         = soap_new_tt__FloatRange(soap);
    ptzs5->XRange->Min    = 0.0;
    ptzs5->XRange->Max    = 1.0;

    ptzs6->URI            = "http://www.onvif.org/ver10/tptz/ZoomSpaces/ZoomGenericSpeedSpace";
    ptzs6->XRange         = soap_new_tt__FloatRange(soap);
    ptzs6->XRange->Min    = 0.0;
    ptzs6->XRange->Max    = 1.0;

    ptzn->MaximumNumberOfPresets = 8;
    ptzn->HomeSupported = true;
    ptzn->FixedHomePosition = (bool *)soap_malloc(soap, sizeof(bool));
    soap_s2bool(soap, "true", ptzn->FixedHomePosition);

    return SOAP_OK;
}

int PTZBindingService::GetNodes(_tptz__GetNodes *tptz__GetNodes, _tptz__GetNodesResponse &tptz__GetNodesResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    soap_default_std__vectorTemplateOfPointerTott__PTZNode(soap, &tptz__GetNodesResponse._tptz__GetNodesResponse::PTZNode);
    tt__PTZNode* ptzn;
    ptzn = soap_new_tt__PTZNode(soap);
    tptz__GetNodesResponse.PTZNode.push_back(ptzn);
    GetPTZNode(this->soap, ptzn);

    return SOAP_OK;
}

int PTZBindingService::GetNode(_tptz__GetNode *tptz__GetNode, _tptz__GetNodeResponse &tptz__GetNodeResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    tptz__GetNodeResponse.PTZNode = soap_new_tt__PTZNode(this->soap);
    GetPTZNode(this->soap, tptz__GetNodeResponse.PTZNode);

    return SOAP_OK;
}

int PTZBindingService::SetConfiguration(_tptz__SetConfiguration *tptz__SetConfiguration, _tptz__SetConfigurationResponse &tptz__SetConfigurationResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GetConfigurationOptions(_tptz__GetConfigurationOptions *tptz__GetConfigurationOptions, _tptz__GetConfigurationOptionsResponse &tptz__GetConfigurationOptionsResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GotoHomePosition(_tptz__GotoHomePosition *tptz__GotoHomePosition, _tptz__GotoHomePositionResponse &tptz__GotoHomePositionResponse)
{
    char cmd[1024];

    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    ServiceContext* ctx = (ServiceContext*)this->soap->user;

    const char *username = soap_wsse_get_Username(this->soap);
    if (!username)
        return this->soap->error;
    if (ctx->user != username)
        return SOAP_FAULT;
    if (soap_wsse_verify_Password(this->soap, ctx->password.c_str()))
        return this->soap->error;

    // Go to preset 1
    sprintf(cmd, "%s 1", ctx->get_ptz_node()->get_move_preset().c_str());
    system(cmd);

    return SOAP_OK;
}

int PTZBindingService::SetHomePosition(_tptz__SetHomePosition *tptz__SetHomePosition, _tptz__SetHomePositionResponse &tptz__SetHomePositionResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::ContinuousMove(_tptz__ContinuousMove *tptz__ContinuousMove, _tptz__ContinuousMoveResponse &tptz__ContinuousMoveResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    ServiceContext* ctx = (ServiceContext*)this->soap->user;

    const char *username = soap_wsse_get_Username(this->soap);
    if (!username)
        return this->soap->error;
    if (ctx->user != username)
        return SOAP_FAULT;
    if (soap_wsse_verify_Password(this->soap, ctx->password.c_str()))
        return this->soap->error;

    if (tptz__ContinuousMove == NULL) {
        return SOAP_OK;
    }
    if (tptz__ContinuousMove->Velocity == NULL) {
        return SOAP_OK;
    }
    if (tptz__ContinuousMove->Velocity->PanTilt == NULL) {
        return SOAP_OK;
    }

    if (tptz__ContinuousMove->Velocity->PanTilt->x > 0) {
        system(ctx->get_ptz_node()->get_move_right().c_str());
    } else if (tptz__ContinuousMove->Velocity->PanTilt->x < 0) {
        system(ctx->get_ptz_node()->get_move_left().c_str());
    }
    if (tptz__ContinuousMove->Velocity->PanTilt->y > 0) {
        system(ctx->get_ptz_node()->get_move_up().c_str());
    } else if (tptz__ContinuousMove->Velocity->PanTilt->y < 0) {
        system(ctx->get_ptz_node()->get_move_down().c_str());
    }

    return SOAP_OK;
}

int PTZBindingService::RelativeMove(_tptz__RelativeMove *tptz__RelativeMove, _tptz__RelativeMoveResponse &tptz__RelativeMoveResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    ServiceContext* ctx = (ServiceContext*)this->soap->user;

    const char *username = soap_wsse_get_Username(this->soap);
    if (!username)
        return this->soap->error;
    if (ctx->user != username)
        return SOAP_FAULT;
    if (soap_wsse_verify_Password(this->soap, ctx->password.c_str()))
        return this->soap->error;

    if (tptz__RelativeMove == NULL) {
        return SOAP_OK;
    }
    if (tptz__RelativeMove->Translation == NULL) {
        return SOAP_OK;
    }
    if (tptz__RelativeMove->Translation->PanTilt == NULL) {
        return SOAP_OK;
    }

    if (tptz__RelativeMove->Translation->PanTilt->x > 0) {
        system(ctx->get_ptz_node()->get_move_right().c_str());
        usleep(300000);
        system(ctx->get_ptz_node()->get_move_stop().c_str());
    } else if (tptz__RelativeMove->Translation->PanTilt->x < 0) {
        system(ctx->get_ptz_node()->get_move_left().c_str());
        usleep(300000);
        system(ctx->get_ptz_node()->get_move_stop().c_str());
    }
    if (tptz__RelativeMove->Translation->PanTilt->y > 0) {
        system(ctx->get_ptz_node()->get_move_up().c_str());
        usleep(300000);
        system(ctx->get_ptz_node()->get_move_stop().c_str());
    } else if (tptz__RelativeMove->Translation->PanTilt->y < 0) {
        system(ctx->get_ptz_node()->get_move_down().c_str());
        usleep(300000);
        system(ctx->get_ptz_node()->get_move_stop().c_str());
    }

    return SOAP_OK;
}

int PTZBindingService::SendAuxiliaryCommand(_tptz__SendAuxiliaryCommand *tptz__SendAuxiliaryCommand, _tptz__SendAuxiliaryCommandResponse &tptz__SendAuxiliaryCommandResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::AbsoluteMove(_tptz__AbsoluteMove *tptz__AbsoluteMove, _tptz__AbsoluteMoveResponse &tptz__AbsoluteMoveResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::Stop(_tptz__Stop *tptz__Stop, _tptz__StopResponse &tptz__StopResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);

    ServiceContext* ctx = (ServiceContext*)this->soap->user;

    const char *username = soap_wsse_get_Username(this->soap);
    if (!username)
        return this->soap->error;
    if (ctx->user != username)
        return SOAP_FAULT;
    if (soap_wsse_verify_Password(this->soap, ctx->password.c_str()))
        return this->soap->error;

    system(ctx->get_ptz_node()->get_move_stop().c_str());

    return SOAP_OK;
}

int PTZBindingService::GetPresetTours(_tptz__GetPresetTours *tptz__GetPresetTours, _tptz__GetPresetToursResponse &tptz__GetPresetToursResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GetPresetTour(_tptz__GetPresetTour *tptz__GetPresetTour, _tptz__GetPresetTourResponse &tptz__GetPresetTourResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GetPresetTourOptions(_tptz__GetPresetTourOptions *tptz__GetPresetTourOptions, _tptz__GetPresetTourOptionsResponse &tptz__GetPresetTourOptionsResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::CreatePresetTour(_tptz__CreatePresetTour *tptz__CreatePresetTour, _tptz__CreatePresetTourResponse &tptz__CreatePresetTourResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::ModifyPresetTour(_tptz__ModifyPresetTour *tptz__ModifyPresetTour, _tptz__ModifyPresetTourResponse &tptz__ModifyPresetTourResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::OperatePresetTour(_tptz__OperatePresetTour *tptz__OperatePresetTour, _tptz__OperatePresetTourResponse &tptz__OperatePresetTourResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::RemovePresetTour(_tptz__RemovePresetTour *tptz__RemovePresetTour, _tptz__RemovePresetTourResponse &tptz__RemovePresetTourResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}

int PTZBindingService::GetCompatibleConfigurations(_tptz__GetCompatibleConfigurations *tptz__GetCompatibleConfigurations, _tptz__GetCompatibleConfigurationsResponse &tptz__GetCompatibleConfigurationsResponse)
{
    DEBUG_MSG("PTZ: %s\n", __FUNCTION__);
    return SOAP_OK;
}
